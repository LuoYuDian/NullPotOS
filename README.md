# NullPotOS

![NullPotOSLogo](docs/img/logo/logo.bmp)

NullPotOS一个免费开源的类UNIX操作系统

# 项目架构

[Projects](docs/NullPotos.md)

## 编译与构建

#### 环境配置

- Linux(Windows下使用WSL2)
- GCC
- G++
- Make
- GDB
- QEMU
- GRUB (制作UEFI的安装grub-efi 制作Legacy的安装grub-pc)

#### 编译

``` Bash
make all
```

#### 调试

``` Bash
make debug
```

#### 也可以使用Github Actions

首先fork本仓库
在到你fork的仓库中
点击Actions
选择NullPotOS Build
点击Run workflow

# 问题
任何问题都可以在Issues中提出

# 开发中!