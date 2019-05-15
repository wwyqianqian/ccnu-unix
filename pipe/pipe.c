#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// fd_arr[2] 父进程写 子进程读
// fd_arr_reverse[2] 子进程写 父进程读

int main(int argc, char *argv[]) {
    pid_t pid;

    int fd_arr[2], fd_arr_reverse[2], i, n;
    char chr; char chr_feedback;

    pipe(fd_arr);
    pipe(fd_arr_reverse);

    pid = fork();

    // child
    if (pid == 0) { // fork() = 0
        close(fd_arr[1]); // close write
        close(fd_arr_reverse[0]);

        for (i = 0; i < 10; i++) {
            chr_feedback = 'z';

            read(fd_arr[0], &chr, 1);
            write(fd_arr_reverse[1], &chr_feedback, 1);
            printf("父进程说：%c\n", chr);

            sleep(1);
           
        }

        close(fd_arr[0]); // close read
        close(fd_arr_reverse[1]);

        exit(0);
    } 

    close(fd_arr[0]); // close read
    close(fd_arr_reverse[1]);



    // parent
    for (i = 0; i < 10; i++) {
        chr = 'a' + i;
        
        write(fd_arr[1], &chr, 1);
        read(fd_arr_reverse[0], &chr_feedback, 1);
        printf("子进程说：%c\n", chr_feedback);

        sleep(1);
    }

    close(fd_arr[1]); // close write
    close(fd_arr_reverse[0]); 
}