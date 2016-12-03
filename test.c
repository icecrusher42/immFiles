#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    int fd, err;
    char buf[100];
    fd = open("./immtestfile.txt", O_CREAT | O_RDWR | O_IMM, 0755);
    if (fd < 0) {
        printf("error opening immediate file\n");
        exit(1);
    }

    write(fd, "wowthisclassisreallygood\0", 7);
    read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content of first slot: %s\n", buf);
}
