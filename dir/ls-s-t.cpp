#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>
#include <getopt.h>

void list(char[]);
void getStat(char *);
void show_file_info(char *,struct stat*);
void default_case (int argc, char *this_argv[]);


void list(char dirname[]) {

    DIR *dir_ptr;
    struct dirent *direntp;
    int countdir = 0;
    int countfile = 0;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "error message: %s \n", strerror(errno));
    }
 
    while ((direntp = readdir(dir_ptr)) != NULL){

        // http://man7.org/linux/man-pages/man3/readdir.3.html
        if (direntp->d_type == DT_DIR) {            
            countdir += 1;
        } else if (direntp->d_type == DT_REG) {
            countfile += 1;
        }

        char s[256];
        sprintf(s, "%s/%s", dirname, direntp->d_name);

        getStat(s); 
    }
    printf("========================\n");
    printf("文件夹数目:%d\n", countdir);
    printf("文件数目:%d\n", countfile);

    closedir(dir_ptr);
}

void getStat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename);
    } else {
        show_file_info(filename, &info);
    }
}

void show_file_info(char *filename, struct stat *info_p) {
    char *ctime();

    printf("%12ld    ", (long)info_p->st_size);
    printf("%.19s     ", ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}

int main(int argc, char *argv[]) {
    // http://man7.org/linux/man-pages/man3/getopt.3.html
    int opt;

    // 输入 -t 选项，按日期从远到近排序; 输入选项 -s，文件按从小到大排序。
    char *string = "st";
    while ((opt = getopt(argc, argv, string)) != -1) {
        switch (opt) {
        case 's':
            printf("-s  文件按从小到大排序:\n");
            break;

        case 't':
            printf("-t  日期从远到近排序:\n");
            break;
        }
    }  

    // 去除掉解析的 -s -t 选项，就是路径（操作数）
    if (argv[optind]) {
        printf("%s\n", argv[optind]); // 操作数，下标从 optind 到 argc - 1。本题只有一个操作数。
        list(argv[optind]);
    } else { 
        list(".");
    }

}





// 测试：
// ./a.out 
// ./a.out ..
// ./a.out -s
// ./a.out -s ..
// ./a.out -t
// ./a.out -t ..


// -----------------------
// extern char *optarg;
// extern int optind;
// extern int optopt;
// extern int opterr;
// extern int optreset;

// int getopt(int argc, char * const argv[], const char *optstring);