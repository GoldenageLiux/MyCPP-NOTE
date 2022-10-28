/**
 * @Author: liuxin
 * @Date:   2022-10-28 21:28:24
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-10-28 21:28:39
 */
#include <stdio.h>

int test = 1;

// 当 static 修饰全局变量时
// 变量的存储区域在全局数据区的静态常量区
// 变量的作用域由整个程序变为当前文件（extern声明也不行）
// 变量的生命周期不变
// 变量的作用域由整个程序变为当前文件
// static int test = 1;