#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#define BUFFER_SIZE 256
int main(void) {
    pid_t pid_fils; 
    int tube[2];
    unsigned char bufferR[256], bufferW[256];
    puts("Creation d'un tube");
    if(pipe(tube) != 0) {
        fprintf(stderr, "Error dans le pipe\n");
        exit(1);
    }
    pid_fils = fork();
    if(pid_fils == -1) {
        fprintf(stderr, "Error dans le fork");
        exit(1);
    }
    if(pid_fils == 0) {
        printf("Fermeture entre dans le fils (pid = %d)\n", getpid());
        close(tube[1]);
        read(tube[0], bufferR, BUFFER_SIZE);
        printf("le fils (%d) a lu : %s\n", getpid(), bufferR);

    }else{
        printf("fermeture sortie dans le pere (pid = %d)\n", getpid());
        close(tube[0]);
        sprintf(bufferW, "Message du pere (%d) au fils", getpid());
        write(tube[1], bufferW, BUFFER_SIZE);
        wait(NULL);
    }
    return 0;
}
