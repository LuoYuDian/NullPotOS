# 创建于2024.12.8
# NullPotOS GRUB 配置文件生成脚本

# /bin/bash

export _OS_NAME=$1
echo $(cat GRUB_TEMPLATE | envsubst)