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
    int opt;
    char *string = "s:t:";
    while ((opt = getopt(argc, argv, string)) != -1) {  
        printf("opt = %c\t\t", opt);
        printf("optarg = %s\t\t", optarg);
        printf("optind = %d\t\t", optind);
        printf("argv[optind] = %s\n", argv[optind]);
    }  

    // if (argc == 1) {
    //     list(".");
    // } else {
    //     while (--argc) { 
    //         printf("%s:\n", *(++argv));
    //         list(*argv);
    //     }
    // }
    
    return 0;
}


// ~/Desktop$  ./a.out -s /Users/qianqian/Desktop -t /Users/qianqian/  

// opt = s     optarg = /Users/qianqian/Desktop        optind = 3      argv[optind] = -t
// opt = t     optarg = /Users/qianqian/       optind = 5      argv[optind] = (null)

// optarg —— 指向当前选项参数(如果有)的指针。
// optind —— 再次调用 getopt() 时的下一个 argv 指针的索引。
