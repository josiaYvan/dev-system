#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int fd;
    FILE *fp;
    char *fileName = "/tmp/test.txt";
    if(mkfifo(fileName, 0644) != 0){
        perror("Problem de creation du noued de tube");
        exit(1);
    }
    fd = open(fileName, O_WRONLY);
    fp = fdopen(fd, "w");
    fprintf(fp, "coucou\n");
    unlink(fileName);
    return 0;
}