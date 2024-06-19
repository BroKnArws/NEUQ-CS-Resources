from matplotlib import pyplot as plt
import os
import numpy as np

file = open("D:/test_log.txt", encoding='utf-8')
sum_acc = 0
train_y = []
loss_y = []
item = 0
sum_loss = 0
for line in file.readlines():
    if item % 2 == 0:
        line = line.strip('\n').split(' ')[4]
        train_y.append(float(line))
        sum_acc = sum_acc + float(line)
        print(float(line))
    else:
        line = line.strip('\n').split(' ')[2]
        loss_y.append(float(line))
        sum_loss = sum_loss + float(line)
        print(float(line))
    item = item + 1
file.close()

train_x = range(0, int(item / 2))
loss_x = range(0, int(item / 2))
train_x_new = []
train_y_new = []
loss_x_new = []
loss_y_new = []

for i in range(len(train_x)):
    if i % 150 == 0:
        train_x_new.append(train_x[i])
        train_y_new.append(train_y[i])
        loss_x_new.append(loss_x[i])
        loss_y_new.append(loss_y[i])

# 用3次多项式拟合
f1 = np.polyfit(train_x_new, train_y_new, 3)
p1 = np.poly1d(f1)
print(p1)  # 打印出拟合函数
train_yvals = p1(train_x_new)  # 拟合y值

# 用3次多项式拟合
f2 = np.polyfit(loss_x_new, loss_y_new, 3)
p2 = np.poly1d(f2)
print(p2)  # 打印出拟合函数
loss_yvals = p2(loss_x_new)  # 拟合y值

fig, ax = plt.subplots(1, 1)
ax.plot(train_x_new, train_y_new, 'r-')
ax1 = ax.twinx()
ax1.plot(train_x_new, loss_y_new, 'b-')
ax.set_xlabel('Train_Batch(Not epoch)')
ax1.set_ylabel('Loss', color='b')
ax.set_ylabel('Accuracy', color='r')
my_y_ticks = np.arange(0, 5.2, 0.2)
my_y_ticks2 = np.arange(0, 101, 10)
ax.set_yticks(my_y_ticks2)
plt.yticks(my_y_ticks)
plt.title('train_accuracy_with_loss')

plt.figure(num=5, figsize=(20, 120))
plt.show()
