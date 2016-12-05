#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define testString "thisisgoingtomakeitgoover40whichisthemaximum"

int main (int argc, char *argv[]) {
    int fd, fd2, err;
    char buf[100];
    fd = open("./immtestfile.txt", O_CREAT | O_RDWR | O_IMM, 0755);
    if (fd < 0) {
        printf("error opening immediate file\n");
        exit(1);
    }

    /* Write, seek, read, seek, read */ 
    err = write(fd, "ABCDEFGH", 8);
    printf("number of chars written = [%d]\n", err);
    lseek(fd, 4, SEEK_SET);

    err = read(fd, buf, 99);
    printf("number of bytes read = [%d]\n", err);
    buf[99] = '\0';
    printf("Buffer content after lseek using SEEK_SET with pos 4: [%s]\n", buf);
    
    lseek(fd, 0, SEEK_SET);
    lseek(fd, -6, SEEK_END);
    memset(&buf[0], 0, sizeof(buf));
    err = read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content after lseek SEEK_END - 6: [%s]\n", buf);

    lseek(fd, -2, SEEK_CUR);
    memset(&buf[0], 0, sizeof(buf));
    err = read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content after SEEK_CUR - 2: [%s]\n", buf);

    lseek(fd, 0, SEEK_SET);
    lseek(fd, -45, SEEK_CUR);
    memset(&buf[0], 0, sizeof(buf));
    err = read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content after SEEK_CUR - 45: [%s]\n", buf);

    printf("Opening in append mode for more testing\n");
    close(fd);
    fd = open("./immtestfile.txt", O_APPEND | O_RDWR);
    write(fd, "12345678", 8);
    memset(&buf[0], 0, sizeof(buf));
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content after appending: [%s]\n", buf);

    printf("Trying to add this string to Immediate file: [%s]\n", testString);
    err = write(fd, testString, strlen(testString) + 1);
    if (err != 0) {
        printf("Error on write to Immediate file: errno = [%d]\n", errno);
    }
    memset(&buf[0], 0, sizeof(buf));
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 99);
    buf[99] = '\0';
    printf("Buffer content after appending: [%s]\n", buf);

    printf("Attemping to create the same file with the O_EXCL flag\n");
    close(fd);
    fd = open("./immtestfile.txt", O_EXCL | O_CREAT | O_IMM, 0755);
    if (fd < 0) {
        printf("Error on opening Immediate file with O_EXCL: errno = [%d]\n", errno);
    }

    /* Regular file creation and reading */
    printf("Now testing regular file creation\n");
    fd2 = open("./regfile.txt", O_CREAT | O_RDWR, 0755);
    if (fd2 < 0) {
        printf("error opening regular file\n");
        exit(1);
    }
    memset(&buf[0], 0, sizeof(buf));
    err = write(fd2, "ABCDE", strlen("ABCDE"));
    lseek(fd2, 0, SEEK_SET);
    err = read (fd2, buf, 99);
    printf("Buffer content of regular file: [%s]\n", buf);

}
