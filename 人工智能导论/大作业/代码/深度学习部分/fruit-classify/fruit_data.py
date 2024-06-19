import os
import numpy as np
from PIL import Image
from matplotlib import pyplot as plt

import torch.utils.data as data


class Fruit(data.Dataset):

    def __init__(self, root_dir, train=True, transform=None):
        # 获取数据集资源目录
        self.root_dir = os.path.abspath(root_dir)
        print(self.root_dir)
        self.transform = transform
        self.train = train

        if (self.train):
            self.data = np.load(os.path.join(self.root_dir, "train", "train_data.npy"), "r+")
            self.labels = np.load(os.path.join(self.root_dir, "train", "train_labels.npy"))
        else:
            self.data = np.load(os.path.join(self.root_dir, "test", "test_data.npy"), "r+")
            self.labels = np.load(os.path.join(self.root_dir, "test", "test_labels.npy"))


    def __getitem__(self, index):
        img, target = self.data[index], self.labels[index]
        img = Image.fromarray(img)

        if self.transform is not None:
            img = self.transform(img)
            img = np.array(img)
        return img, target

    def __len__(self):
        return (len(self.data))
