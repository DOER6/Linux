#!/bin/bash

# 提示用户输入三个数字
echo "请输入三个数字，以空格分隔："
read num1 num2 num3

# 计算和
sum=$((num1 + num2 + num3))

# 显示结果
echo "这三个数字的和为：$sum"
