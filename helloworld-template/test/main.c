#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "../helloworld.h"

static const char *DEVICE_NAME = "/dev/helloworld";

int main()
{
    // O_NONBLOCK
    int fd = open(DEVICE_NAME, O_RDWR); // 触发 helloworld_open
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    printf("DeviceName: [%s] open successed.\n", DEVICE_NAME);


    printf("CMD code: HELP.\n");
    if (0 != ioctl(fd, HELLOWORLD_IOC_HELP)) // 触发 helloworld_ioctl
    {
        perror("HELP");
        return -1;
    }
    getchar();

    printf("CMD code: RESET.\n");
    if (0 != ioctl(fd, HELLOWORLD_IOC_RESET))
    {
        perror("RESET");
        return -1;
    }
    getchar();


    printf("CMD code: DESCRIPTION.\n");
    char description[DESCRIPTION_MAXSIZE];
    if (0 != ioctl(fd, HELLOWORLD_IOR_DESCRIPTION, description))
    {
        perror("DESCRIPTION");
        return -1;
    }
    printf("Description: %s\n", description);
    getchar();


    printf("CMD code: AUTHOR.\n");
    char author[AUTHOR_MAXSIZE];
    if (0 != ioctl(fd, HELLOWORLD_IOR_AUTHOR, author))
    {
        perror("AUTHOR");
        return -1;
    }
    printf("Author: %s\n", author);
    getchar();


    printf("CMD code: VERSION.\n");
    char version[VERSION_MAXSIZE];
    if (0 != ioctl(fd, HELLOWORLD_IOR_VERSION, version))
    {
        perror("VERSION");
        return -1;
    }
    printf("Version: %s\n", version);
    getchar();


    printf("CMD code: LICENSE.\n");
    char license[LICENSE_MAXSIZE];
    if (0 != ioctl(fd, HELLOWORLD_IOR_LICENSE, license))
    {
        perror("LICENSE");
        return -1;
    }
    printf("License: %s\n", license);
    getchar();


    printf("CMD code: VERBOSE_STATUS.\n");
    int verboseStatus = STATUS_OFF;
    if (0 != ioctl(fd, HELLOWORLD_IOR_VERBOSE_STATUS, &verboseStatus))
    {
        perror("VERBOSE_STATUS");
        return -1;
    }
    printf("GET VerboseStatus: %d\n", verboseStatus);
    getchar();


    printf("CMD code: VERBOSE_ENABLE.\n");
    if (verboseStatus)
    {
        verboseStatus = STATUS_OFF;
    }
    else
    {
        verboseStatus = STATUS_ON;
    }
    if (0 != ioctl(fd, HELLOWORLD_IOW_VERBOSE_ENABLE, &verboseStatus))
    {
        perror("VERBOSE_ENABLE");
        return -1;
    }
    printf("SET VerboseStatus: %d\n", verboseStatus);

    if (0 != ioctl(fd, HELLOWORLD_IOR_VERBOSE_STATUS, &verboseStatus))
    {
        perror("VERBOSE_STATUS");
        return -1;
    }
    printf("GET VerboseStatus: %d\n", verboseStatus);
    getchar();


    printf("CMD code: TOKEN.\n");
    struct TOKEN_S tokenContext;
    tokenContext.dir = DIR_READ;
    if (0 != ioctl(fd, HELLOWORLD_IOWR_TOKEN, &tokenContext))
    {
        perror("READ TOKEN");
        return -1;
    }
    printf("Read Token: Key: %s, Salt: %s\n", tokenContext.key, tokenContext.salt);

    tokenContext.dir = DIR_WRITE;
    strncpy(tokenContext.key, "0123456789", sizeof("0123456789"));
    strncpy(tokenContext.salt, "9876543210", sizeof("9876543210"));
    if (0 != ioctl(fd, HELLOWORLD_IOWR_TOKEN, &tokenContext))
    {
        perror("WRITE TOKEN");
        return -1;
    }
    printf("Update Token finished.\n");

    tokenContext.dir = DIR_READ;
    if (0 != ioctl(fd, HELLOWORLD_IOWR_TOKEN, &tokenContext))
    {
        perror("READ TOKEN");
        return -1;
    }
    printf("Check Token: Key: %s, Salt: %s\n", tokenContext.key, tokenContext.salt);

    // Reset
    tokenContext.dir = DIR_WRITE;
    strncpy(tokenContext.key, "zta0724", sizeof("zta0724"));
    strncpy(tokenContext.salt, "zta0724@qq.com", sizeof("zta0724@qq.com"));
    if (0 != ioctl(fd, HELLOWORLD_IOWR_TOKEN, &tokenContext))
    {
        perror("WRITE TOKEN");
        return -1;
    }
    printf("Reset Token finished.\n");

    if (0 != close(fd))
    {
        perror("close");
        return -1;
    }

    printf("DeviceName: [%s] close successed.\n", DEVICE_NAME);

    return 0;
}
