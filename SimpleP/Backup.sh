#!/bin/bash

# 源文件或目录
source_dir="/home/rainw920/BaseCode"
# 目标备份目录
backup_dir="/home/rainw920/Autobackup"
# 备份文件名，可以根据日期来命名
backup_filename="backup_$(date +\%Y\%m\%d).tar.gz"

# 创建备份
rsync -a --delete "$source_dir" "$backup_dir/$backup_filename"

# 可选：删除旧备份文件，只保留最近几个备份
find "$backup_dir" -type f -mtime +7 -exec rm {} \;

echo "备份完成：$backup_filename"

