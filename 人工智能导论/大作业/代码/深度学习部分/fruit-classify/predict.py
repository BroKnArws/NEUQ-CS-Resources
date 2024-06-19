import torch
import torch.nn as nn
from torchvision import transforms
from torch.utils.data import DataLoader
import fruit_data
import torch.nn.functional as F
from sklearn.metrics import accuracy_score
from PIL import Image
import os
import logger
import sys
import train_plus_plus

device = torch.device("cuda") if (torch.cuda.is_available()) else torch.device("cpu")


def predict(img_folder_path):
    img_files = os.listdir(img_folder_path)
    data_transforms = transforms.Compose(
        [
            transforms.Resize((size, size)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
        ])
    net = train_plus_plus.FruitNet()
    net.load_state_dict(torch.load("./model/fruit_model_state_dict.pth"))
    net = net.to(device)
    torch.no_grad()
    net.eval()
    for img_file in img_files:
        print("-----------------------")
        print(f"文件名是: {img_file}")
        print("-----------------------")
        img_path = os.path.join(img_folder_path, img_file)
        img = Image.open(img_path)
        img = data_transforms(img).unsqueeze(0)
        # print(type(img))
        img = img.to(device)

        pred = net(img)
        pred_sorted_like = torch.sort(pred, descending=True)[0].data.numpy()[0]
        pred_sorted_label = torch.sort(pred, descending=True)[1].data.numpy()[0]
        sum = 0
        for i in range(4):
            sum = sum + pred_sorted_like[i]
        for i in range(4):
            print('我觉得这个图片可能是 :', labels[pred_sorted_label[i]])
            print(f'可能性是 :{round((sum - pred_sorted_like[i]) / sum * 100, 2)} % ')


if __name__ == '__main__':
    size = 100
    image_path = "dataset"

    folder_paths = os.path.join(image_path, "Training")
    labels = os.listdir(folder_paths)
    predict("./TestImage")
