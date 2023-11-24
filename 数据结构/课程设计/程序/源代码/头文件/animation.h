#pragma once

#include<iomanip>
#include<iostream>
#include <stdio.h>

using namespace std;

/* 装饰：进度条动画 */
void processAnimation(int process, int end);

/* 装饰：菜单界面 */
int menuShow();

/* 报错处理 */
void Exception(int num);