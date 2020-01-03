/*
 * Author: zta0724 <zta0724@qq.com>
 * WebSite: https://github.com/zta0724/helloworld-module.git
 * Version: v0.0.1
 * License: MIT
 *
 * 通用Linux驱动模块模板, 示例:
 *  1. 把 helloworld 替换成你的 modulename
 *  2. 把 HELLOWORLD 替换成你的 MODULENAME
 *  3. 把 helloworld.h 重命名成你的 modulename.h
 *  4. 把 helloworld.c 重命名成你的 modulename.c
 *  5. 更新字段内容: THIS_LICENSE / THIS_VERSION / THIS_AUTHOR / THIS_DESCRIPTION
 *  6. 把 Makefile 中的 obj-m := helloworld.o 替换成你的 obj-m := modulename.o
 */
#ifndef MODULE_HELLOWORLD_H
#define MODULE_HELLOWORLD_H

// NR
enum {
    NR_HELP = 0,
    NR_RESET,
    NR_DESCRIPTION,
    NR_AUTHOR,
    NR_VERSION,
    NR_LICENSE,
    NR_VERBOSE_STATUS,
    NR_VERBOSE_ENABLE,
    NR_TOKEN,
    NR_MAX
};

// TYPE
#define HELLOWORLD_IOC_MAGIC 'z'
//#define HELLOWORLD_IOC_MAGIC 0x5A

#define DESCRIPTION_MAXSIZE 128
#define AUTHOR_MAXSIZE       64
#define VERSION_MAXSIZE      16
#define LICENSE_MAXSIZE      32

#define STATUS_OFF 0
#define STATUS_ON  1

#define DIR_READ   0
#define DIR_WRITE  1

#define KEY_MAXSIZE  32
#define SALT_MAXSIZE 32

struct TOKEN_S {
    int dir;
    char key[KEY_MAXSIZE];
    char salt[SALT_MAXSIZE];
};

/*
 * CMD code:
 * -------------------------------------------------------------------
 * | 31-30 (2 bits) | 29-16 (14 bits) | 15-8 (8 bits) | 7-0 (8 bits) |
 * -------------------------------------------------------------------
 * |       DIR      |       SIZE      |      TYPE     |     NR       |
 * -------------------------------------------------------------------
 */
#define HELLOWORLD_IOC_HELP             _IO(HELLOWORLD_IOC_MAGIC, NR_HELP)
#define HELLOWORLD_IOC_RESET            _IO(HELLOWORLD_IOC_MAGIC, NR_RESET)
#define HELLOWORLD_IOR_DESCRIPTION      _IOR(HELLOWORLD_IOC_MAGIC, NR_DESCRIPTION, char [DESCRIPTION_MAXSIZE])
#define HELLOWORLD_IOR_AUTHOR           _IOR(HELLOWORLD_IOC_MAGIC, NR_AUTHOR, char [AUTHOR_MAXSIZE])
#define HELLOWORLD_IOR_VERSION          _IOR(HELLOWORLD_IOC_MAGIC, NR_VERSION, char [VERSION_MAXSIZE])
#define HELLOWORLD_IOR_LICENSE          _IOR(HELLOWORLD_IOC_MAGIC, NR_LICENSE, char [LICENSE_MAXSIZE])
#define HELLOWORLD_IOR_VERBOSE_STATUS   _IOR(HELLOWORLD_IOC_MAGIC, NR_VERBOSE_STATUS, int)
#define HELLOWORLD_IOW_VERBOSE_ENABLE   _IOW(HELLOWORLD_IOC_MAGIC, NR_VERBOSE_ENABLE, int)
#define HELLOWORLD_IOWR_TOKEN           _IOWR(HELLOWORLD_IOC_MAGIC, NR_TOKEN, struct TOKEN_S)

#define HELLOWORLD_IOC_MAXNR NR_MAX

#endif // MODULE_HELLOWORLD_H
