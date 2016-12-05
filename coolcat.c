#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main (int argc, char* argv[]) { 
    FILE *finput;
    int err;
	char buf[100];

    finput = fopen("immtestfile.txt", "a+");
    if (finput == NULL) {
    	printf("File is null on fopen\n");
    	perror("Error");
    }

    if (feof(finput)) {
    	printf("end of file input\n");
    }
    fscanf(finput, "%s", buf);
    buf[99] = '\0';
    printf("Buffer content after opening using fopen: [%s]\n", buf);

    fprintf(finput, "moreTEXT");
    memset(&buf[0], 0, sizeof(buf));
    fseek(finput, 0, SEEK_SET);
    fscanf(finput, "%s", buf);
    buf[99] = '\0';
    printf("Buffer content after writing using fprintf: [%s]\n", buf);
}