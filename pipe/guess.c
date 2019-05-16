#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

const int NUM = 50;

// fd_arr[2] 父进程写 子进程读
// fd_arr_reverse[2] 子进程写 父进程读
// 1. [子]假如子那里有个50，
// 2. [父] 父写一个 100，
// 3. [子] 子读一个 100，
// 4. [子] 子比较 100 > 50，
// 5. [子] 子写: 大了，
// 6. [父] 父读: 大了，
// 7. [父] 父继续写，
// 8. jump -> 3

int main(int argc, char *argv[]) {
    int fd_arr[2], fd_arr_reverse[2];
    pipe(fd_arr);
    pipe(fd_arr_reverse);

    pid_t pid = fork();

    // parent
    if (pid > 0) {
        close(fd_arr[0]); // close read
        close(fd_arr_reverse[1]);
        int guess_num = 0; char chr_feedback[256] = "";

        do {
            scanf("%d", &guess_num);

            write(fd_arr[1], &guess_num, 256);
            read(fd_arr_reverse[0], &chr_feedback, 256);
            printf("子进程说：%s\n", chr_feedback);
        
            sleep(1);

        } while (strcmp(chr_feedback, "大了") == 0 || strcmp(chr_feedback, "小了") == 0);

        close(fd_arr[1]); // close write
        close(fd_arr_reverse[0]); 

    }
    // child
    else { // fork() = 0    
        close(fd_arr[1]); // close write
        close(fd_arr_reverse[0]);
        int guess_num = 0; char chr_feedback[256] = "";

        do {
            read(fd_arr[0], &guess_num, 256);
            printf("父进程说我猜的是：%d\n", guess_num);

            if (guess_num > NUM) {
                strcpy(chr_feedback, "大了"); 
            }
            if (guess_num < NUM) {
                strcpy(chr_feedback, "小了"); 
            }
            if (guess_num == NUM) {
                strcpy(chr_feedback, "正好"); 
            }

            write(fd_arr_reverse[1], &chr_feedback, 256);
            sleep(1);

        } while (guess_num != NUM);

        close(fd_arr[0]); // close read
        close(fd_arr_reverse[1]);

    }
}