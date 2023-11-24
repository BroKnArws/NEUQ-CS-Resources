from PIL import Image
from model_service.pytorch_model_service import PTServingBaseService
import torch.nn.functional as F
import torch.nn as nn
import torch
import json
import numpy as np
import torchvision.transforms as transforms
import os
import logging

logger = logging.getLogger(__name__)
# 定义模型预处理
data_transforms = transforms.Compose(
    [
        transforms.Resize((100, 100)),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
    ])


class PTVisionService(PTServingBaseService):

    def __init__(self, model_name, model_path):
        # 调用父类构造方法
        super(PTVisionService, self).__init__(model_name, model_path)
        logger.info('model_name: ', model_name)
        logger.info('model_path: ', model_path)
        # 调用自定义函数加载模型
        self.model_name = model_name
        self.model = get_model(model_path)
        # 加载标签
        self.label = ['Apple Braeburn', 'Apple Crimson Snow', 'Apple Golden 1', 'Apple Golden 2', 'Apple Golden 3',
                      'Apple Granny Smith', 'Apple Pink Lady', 'Apple Red 1', 'Apple Red 2', 'Apple Red 3',
                      'Apple Red Delicious', 'Apple Red Yellow 1', 'Apple Red Yellow 2', 'Apricot', 'Avocado',
                      'Avocado ripe',
                      'Banana', 'Banana Lady Finger', 'Banana Red', 'Beetroot', 'Blueberry', 'Cactus fruit',
                      'Cantaloupe 1',
                      'Cantaloupe 2', 'Carambula', 'Cauliflower', 'Cherry 1', 'Cherry 2', 'Cherry Rainier',
                      'Cherry Wax Black',
                      'Cherry Wax Red', 'Cherry Wax Yellow', 'Chestnut', 'Clementine', 'Cocos', 'Corn', 'Corn Husk',
                      'Cucumber Ripe', 'Cucumber Ripe 2', 'Dates', 'Eggplant', 'Fig', 'Ginger Root', 'Granadilla',
                      'Grape Blue',
                      'Grape Pink', 'Grape White', 'Grape White 2', 'Grape White 3', 'Grape White 4', 'Grapefruit Pink',
                      'Grapefruit White', 'Guava', 'Hazelnut', 'Huckleberry', 'Kaki', 'Kiwi', 'Kohlrabi', 'Kumquats',
                      'Lemon',
                      'Lemon Meyer', 'Limes', 'Lychee', 'Mandarine', 'Mango', 'Mango Red', 'Mangostan', 'Maracuja',
                      'Melon Piel de Sapo', 'Mulberry', 'Nectarine', 'Nectarine Flat', 'Nut Forest', 'Nut Pecan',
                      'Onion Red',
                      'Onion Red Peeled', 'Onion White', 'Orange', 'Papaya', 'Passion Fruit', 'Peach', 'Peach 2',
                      'Peach Flat',
                      'Pear', 'Pear 2', 'Pear Abate', 'Pear Forelle', 'Pear Kaiser', 'Pear Monster', 'Pear Red',
                      'Pear Stone',
                      'Pear Williams', 'Pepino', 'Pepper Green', 'Pepper Orange', 'Pepper Red', 'Pepper Yellow',
                      'Physalis',
                      'Physalis with Husk', 'Pineapple', 'Pineapple Mini', 'Pitahaya Red', 'Plum', 'Plum 2', 'Plum 3',
                      'Pomegranate', 'Pomelo Sweetie', 'Potato Red', 'Potato Red Washed', 'Potato Sweet',
                      'Potato White',
                      'Quince', 'Rambutan', 'Raspberry', 'Redcurrant', 'Salak', 'Strawberry', 'Strawberry Wedge',
                      'Tamarillo',
                      'Tangelo', 'Tomato 1', 'Tomato 2', 'Tomato 3', 'Tomato 4', 'Tomato Cherry Red', 'Tomato Heart',
                      'Tomato Maroon', 'Tomato not Ripened', 'Tomato Yellow', 'Walnut', 'Watermelon']

    def _preprocess(self, data):
        logger.info("_preprocess begin")
        preprocessed_data = {}
        for k, v in data.items():
            for file_name, file_content in v.items():
                image = Image.open(file_content)
                img = data_transforms(image)
                logger.info("transforms OK")
                preprocessed_data[k] = img.unsqueeze(0)
                logger.info(preprocessed_data[k])
        logger.info("_preprocess OK")
        return preprocessed_data

    def _inference(self, data):
        logger.info("_inference begin")
        for k, v in data.items():
            logger.info("k is :" + k)
            pred = self.model(v)
            pred_sorted_label = torch.sort(pred, descending=True)[1].data.numpy()[0]
            result = self.label[pred_sorted_label[0]]
            res = {'prediction': "I think it maybe :" + result}
            logger.info("_inference OK")
            return res

    def _postprocess(self, data):
        logger.info("_postprocess begin")
        return data


# 水果识别模型
class FruitNet(nn.Module):
    def __init__(self):
        super(FruitNet, self).__init__()

        # N=(W-F+2P)/S+1
        # in_channels = 3,out channels = 16,kernel_size = 5
        # output_size = (100-5+1)*(100-5+1)*16 =
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=16, kernel_size=5)
        self.bn1 = nn.BatchNorm2d(16)
        # output_size = ((96-2)/2+1)*((96-2)/2+1)*16
        self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)
        # in_channels = 16,out channels = 32,kernel_size = 5
        # output_size = (48-5+1)*(48-5+1)*32
        self.conv2 = nn.Conv2d(16, 32, 5)
        self.bn2 = nn.BatchNorm2d(32)
        # output_size = ((44-2)/2+1)*((44-2)/2+1)*32
        self.pool2 = nn.MaxPool2d(2, 2)
        # in_channels = 32,out channels = 64,kernel_size = 5
        # output_size = (22-5+1)*(22-5+1)*64
        self.conv3 = nn.Conv2d(32, 64, 5)
        self.bn3 = nn.BatchNorm2d(64)
        # output_size = ((18-2)/2+1)*((18-2)/2+1)*64
        self.pool3 = nn.MaxPool2d(2, 2)
        # in_channels = 64,out channels = 128,kernel_size = 5
        # output_size = (9-5+1)*(9-5+1)*64
        self.conv4 = nn.Conv2d(64, 128, 5)
        self.bn4 = nn.BatchNorm2d(128)
        # output_size = ((5-3)/2+1)*((5-3)/2+1)*128
        self.pool4 = nn.MaxPool2d(3, 2)

        self.linear1 = nn.Linear(2 * 2 * 128, 256)
        self.linear2 = nn.Linear(256, 131)

    def forward(self, x):
        x = self.pool1(F.relu(self.bn1(self.conv1(x))))
        x = self.pool2(F.relu(self.bn2(self.conv2(x))))
        x = self.pool3(F.relu(self.bn3(self.conv3(x))))
        x = self.pool4(F.relu(self.bn4(self.conv4(x))))
        x = x.view(x.size(0), -1)
        x = F.relu(self.linear1(x))
        x = F.log_softmax(self.linear2(x), dim=1)

        return x


def get_model(model_path, **kwargs):
    # 生成网络
    model = FruitNet()
    # 加载模型
    device = torch.device('cpu')
    model.load_state_dict(torch.load(model_path))
    model.to(device)
    torch.no_grad()
    # 声明为推理模式
    model.eval()
    logger.info("get_model OK")

    return model
