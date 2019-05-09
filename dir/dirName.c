// 列出某目录下文件名
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    DIR *dirp;
    struct dirent *direntp;
    dirp = opendir(argv[1]);

    if (dirp == NULL) {
    fprintf(stderr, "error message: %s \n", strerror(errno)); // print error
    printf("正确语法：./a.out /the/path");
        exit(1);
    }

    while ((direntp = readdir(dirp)) != NULL) {
        printf("%s\n", direntp->d_name);
    }
    closedir(dirp);

    exit(0);
}


// ~/Desktop  gcc /Users/qianqian/Desktop/mydir.c       
// ~/Desktop  ./a.out /Users/qianqian/
