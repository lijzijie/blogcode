#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>

int main()
{
    //打开设备文件
    int fd = open("/dev/mytest_device", O_RDWR);
    if (fd < 0) {
        printf("Open error\n");
        return -1;
    }
    printf("fd:%d\n", fd);

    //创建 struct polld 结构体，并为其中的成员赋值
    struct pollfd fds[1];
    fds[0].fd = fd;                // 指定文件描述
    fds[0].events = POLLIN;        // 要监听的事件，有数据可以读的时候返回
    fds[0].revents = 0;            // 实际返回的事件

    int ret = 0;            //poll 函数的返回值，依据返回值判断是否有数据可读

    //循环查询
    while(1) {
        ret = poll(fds, 1, -1); // -1表示一直在等待

        if(ret > 0 && fds[0].revents == POLLIN)
            printf("status Change\n");
    }
    close(fd);
    return 0;
}
