#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main() {
    //pid demande input to user and ppid screen it
        int fd[2];
        //fd[0] - read
        //fd[1] - writte
        if(pipe(fd) == -1) {
            printf("An error ocured with opening the pipe\n");
            return 1;
        }

        int id  = fork();
        if(id == -1 ){
            printf("An errror ocured with fork()\n");
            return 4;
        }

        if (id == 0 ) {//ppid
            close(fd[0]);
            int x; 
            printf("input a number:\n");
            scanf("%d", &x);
            if (write(fd[1], &x, sizeof(int)) == -1){
                printf("An errror ocured with writing to the pipe\n");
                return 2;
            }
            close(fd[1]);
           // printf("Got from parent process %d\n", x);
        }else{//ppid
            int y;
            if(read(fd[0], &y, sizeof(int)) == -1){
                printf("An errror ocured with reading from the pipe\n");
                return 3;
            }
            close(fd[0]);
            printf("Got from child process %d\n", y);
        }
        
    return 0;
}