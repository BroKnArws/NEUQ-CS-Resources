import os
import numpy as np
from matplotlib import pyplot as plt

image_path = "dataset"

folder_paths = os.path.join(image_path, "Training")
fruit_names = os.listdir(folder_paths)
print(fruit_names)
print(f"INFO:  训练集图片的路径是 : {image_path}")
print(f"INFO: 测试的标签种类有 {len(fruit_names)} 个")

print("INFO ：正在保存训练集。。。")
# 加载数据集
train_data = []
train_labels = []
for fruit in fruit_names:

    folder_path = os.path.join(image_path, "Training", fruit)
    images = os.listdir(folder_path)

    for i in range(len(images)):
        final_path = os.path.join(folder_path, images[i])
        img = plt.imread(final_path)
        train_data.append(img)
        train_labels.append(fruit_names.index(fruit))
    print(fruit, " 完毕")

train_data = np.array(train_data)
train_labels = np.array(train_labels)

print("INFO ：正在保存到.npy文件中。。。")

# 保存数据文件.
np.save('./npy/train/train_data.npy', train_data)
np.save('./npy/train/train_labels.npy', train_labels)

print("INFO ：训练集保存完毕。")


print("INFO ：正在保存测试集。。。")
# 读取测试集
test_data = []
test_labels = []
for fruit in fruit_names:
    print(fruit)
    folder_path = os.path.join(image_path, "Test", fruit)
    images = os.listdir(folder_path)

    for image in images:
        final_path = os.path.join(folder_path, image)
        if not os.path.isfile(final_path):
            print(f"路径不存在 : {final_path}")
            continue
        img = plt.imread(final_path)
        test_data.append(img)
        test_labels.append(fruit_names.index(fruit))

test_data = np.array(test_data)
test_labels = np.array(test_labels)

print("INFO ：正在保存到.npy文件中。。。")

# 保存数据文件.
np.save('./npy/test/test_data.npy', test_data)
np.save('./npy/test/test_labels.npy', test_labels)

print("INFO : 测试集保存完毕。")