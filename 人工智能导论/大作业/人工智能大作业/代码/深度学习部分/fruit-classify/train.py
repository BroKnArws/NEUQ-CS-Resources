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

device = torch.device("cuda") if (torch.cuda.is_available()) else torch.device("cpu")


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


# 训练模型
def train_network(dataloader_train):
    net = FruitNet()
    net = net.to(device)
    # 随机梯度下降法
    optimizer = torch.optim.SGD(net.parameters(), lr=0.03, momentum=0.9)
    criterion = nn.CrossEntropyLoss()
    net.train()

    for epoch in range(epochs):
        print(f"开始第 {epoch + 1} 批")
        for i_batch, (images, labels) in enumerate(dataloader_train):
            images, labels = images.to(device), labels.to(device)
            x = images.float()
            y = labels.long()
            optimizer.zero_grad()
            y_pred = net(x)
            # 取正确率
            correct = y_pred.max(1)[1].eq(y).sum()
            print("INFO : 训练准确率 : {} %".format(round(correct.item() / len(labels) * 100, 3)))
            loss = criterion(y_pred, y)
            print("Loss : {}".format(loss.item()))
            loss.backward()
            optimizer.step()

    # 保存训练模型参数
    torch.save(net.state_dict(), "./model/fruit_model_state_dict.pth")
    print("INFO: 总共完成了 {} 批".format(epochs + 1))

    return net


# 测试模型
def test_network(net, dataloader_test):
    net.eval()
    criterion = nn.CrossEntropyLoss()
    accuracies = []
    with torch.no_grad():
        for feature, label in dataloader_test:
            feature = feature.to(device)
            label = label.to(device).long()
            pred = net(feature)
            # 要在cpu上完成
            accuracy = accuracy_score(label.cpu().data.numpy(), pred.max(1)[1].cpu().data.numpy()) * 100
            print(f"正确率: {round(accuracy, 3)} %")
            loss = criterion(pred, label).item()
            print(f"loss : {loss}")
            accuracies.append(accuracy)

    # 计算平均正确率
    total = 0.0
    for j in range(len(accuracies)):
        total = total + accuracies[j]
    avg_acc = total / len(accuracies)
    print(f"TOTAL : 经测试得出的识别准确率是: {round(avg_acc, 3)} %")


# 主函数
def main():
    # 数据增强
    data_transform_train = transforms.Compose(
        [
            transforms.RandomGrayscale(p=0.1),
            transforms.RandomRotation(20),
            transforms.RandomHorizontalFlip(),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.5, 0.5, 0.5],
                                 std=[0.5, 0.5, 0.5])])

    data_transform_test = transforms.Compose(
        [
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.5, 0.5, 0.5],
                                 std=[0.5, 0.5, 0.5])])

    transformed_dataset = fruit_data.Fruit(data_dir,
                                           train=True,
                                           transform=data_transform_train)

    dataloader_train = DataLoader(transformed_dataset,
                                  batch_size=64,
                                  shuffle=True)

    transformed_test_dataset = fruit_data.Fruit(data_dir,
                                                train=False,
                                                transform=data_transform_test)

    dataloader_test = DataLoader(transformed_test_dataset,
                                 batch_size=64,
                                 shuffle=True)

    data_iter = iter(dataloader_train)
    images, labels = next(data_iter)
    print("INFO: 图像的尺寸是 {}".format(images.shape))
    print("INFO: 图像 Tensor 的类型是 : {}".format(images.type()))
    print("INFO: 标签的尺寸是 : {}".format(labels.shape))
    print("INFO: 标签 Tensor 的类型是 : {}".format(labels.type()))

    # 训练模型
    net = train_network(dataloader_train)
    # 加载模型
    # net = FruitNet()
    # net.load_state_dict(torch.load("./model/fruit_model_state_dict.pth"))
    # 测试模型
    test_network(net, dataloader_test)


if __name__ == '__main__':
    size = 100
    training_dataset_path = "./dataset/Training"
    data_dir = "./npy"
    epochs = 10
    sys.stdout = logger.Logger("./logs/test_log.txt")
    main()
