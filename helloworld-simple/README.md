## 查看内核版本
$ uname -r
4.15.0-72-generic

## 查看内核头文件
$ ll /usr/src/ | grep linux-headers-4.15.0.72
drwxr-xr-x 25 root root 4096 12月  4 18:30 linux-headers-4.15.0-72/
drwxr-xr-x  8 root root 4096 12月  4 18:30 linux-headers-4.15.0-72-generic/

## 编译HelloWorld驱动模块
$ make
make -C /usr/src/linux-headers-4.15.0-72-generic M=/home/zta/Desktop/GitHub/helloworld-module/helloworld-simple modules
make[1]: Entering directory '/usr/src/linux-headers-4.15.0-72-generic'
  CC [M]  /home/zta/Desktop/GitHub/helloworld-module/helloworld-simple/helloworld.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/zta/Desktop/GitHub/helloworld-module/helloworld-simple/helloworld.mod.o
  LD [M]  /home/zta/Desktop/GitHub/helloworld-module/helloworld-simple/helloworld.ko
make[1]: Leaving directory '/usr/src/linux-headers-4.15.0-72-generic'

## 查看文件信息
$ ll ./helloworld.ko
-rw-rw-r-- 1 zta zta 4128 1月   3 19:33 ./helloworld.ko

$ file ./helloworld.ko 
./helloworld.ko: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), BuildID[sha1]=92b300241d8f67f2710ba7e3135ec93b149191a0, not stripped

## 查看模块信息
$ modinfo ./helloworld.ko 
filename:       /home/zta/Desktop/GitHub/helloworld-module/helloworld-simple/./helloworld.ko
description:    https://github.com/zta0724/helloworld-module.git
author:         zta0724 <zta0724@qq.com>
version:        0.0.1
license:        Dual MIT/GPL
srcversion:     19BFE5DACD908AAACB03B52
depends:        
retpoline:      Y
name:           helloworld
vermagic:       4.15.0-72-generic SMP mod_unload 

## 动态加载模块
$ sudo insmod ./helloworld.ko
$ dmesg
[ 1789.668272] [HELLOWORLD] init.

## 查看模块状态
$ lsmod | grep helloworld
helloworld             16384  0

## 卸载模块
$ sudo rmmod helloworld
$ dmesg
[ 1879.405385] [HELLOWORLD] exit.

