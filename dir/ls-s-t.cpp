#include <string.h>
#include <time.h>
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

struct stat *list(char[], struct stat infos[]);
struct stat getStat(char *);

long cmpBySize (struct stat *a, struct stat *b);
long cmpByDate (struct stat *a, struct stat *b);
void printDefalt();
void printBySize();
void printByDate();


struct stat infos[256]; // 定义 struct stat 类型的数组用来存放 info 结构体。
int countdir = 0;
int countfile = 0;

struct stat *list(char dirname[], struct stat infos[]) {

    DIR *dir_ptr;
    struct dirent *direntp;


    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "error message: %s \n", strerror(errno));
    }
 
    
    int infos_index = 0;
    while ((direntp = readdir(dir_ptr)) != NULL) {

        // http://man7.org/linux/man-pages/man3/readdir.3.html
        if (direntp->d_type == DT_DIR) {            
            countdir += 1;
        } else if (direntp->d_type == DT_REG) {
            countfile += 1;
        }

        char s[256];
        sprintf(s, "%s/%s", dirname, direntp->d_name);

        struct stat this_info = getStat(s); 
        infos[infos_index] = this_info;
        infos_index++; 
    }

    closedir(dir_ptr);
    return infos;
}

struct stat getStat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename);
    } else {
        return info;
    }
}


void printDefault() {
    for (int i = 0; infos[i].st_size > 0; ++i) {
        printf("%12ld    ", (long)infos[i].st_size);
        printf("%.24s     \n", ctime(&infos[i].st_mtime));  
        // printf("%s\n", filename);      
    }

}

void printBySize() {
    qsort(infos, countdir + countfile, sizeof(struct stat), cmpBySize);
    printDefault();

}

void printByDate() {
    qsort(infos, countdir + countfile, sizeof(struct stat), cmpByDate);
    printDefault();
}


long cmpBySize (struct stat *a, struct stat *b) {
   return (a->st_size - b->st_size);
}

long cmpByDate (struct stat *a, struct stat *b) {
    return (a->st_mtime - b->st_mtime);
}


int main(int argc, char const *argv[]) {
    int opt;
    int stat_flag = 0; // stat_flag, 0 是 -s，1 是 -t
    int path_flag = 0; // path_flag, 0 是当前(.)，1 是所键入的目录
    
    // 输入 -t 选项，按日期从远到近排序; 输入选项 -s，文件按从小到大排序。
    // http://man7.org/linux/man-pages/man3/getopt.3.html

    char *string = "st";
    while ((opt = getopt(argc, argv, string)) != -1) {
        switch (opt) {
        case 's':
            printf("-s  文件按从小到大排序:\n");
            stat_flag = 0;
            break;

        case 't':
            printf("-t  日期从远到近排序:\n");
            stat_flag = 1;
            break;

        default: 
            printf("Unknown option!");
        }
    }  

    if (argv[optind]) {
        printf("含路径排序:\n");
        // printf("%s\n", argv[optind]); // 操作数，下标从 optind 到 argc - 1。本题只有一个操作数。
        path_flag = 1;
    } else { 
        printf("无路径排序:\n");
        // list(".", infos);
        path_flag = 0;
    }


    if (stat_flag == 0 && path_flag == 0) {
        list(".", infos);
        printBySize();
    } else if (stat_flag == 0 && path_flag == 1) {
        list(argv[optind], infos);
        printBySize();
    } else if (stat_flag == 1 && path_flag == 0) {
        list(".", infos);
        printByDate();        
    } else if (stat_flag == 1 && path_flag == 1) {
        list(argv[optind], infos);
        printByDate();
    }


    printf("========================\n");
    printf("文件夹数目:%d\n", countdir);
    printf("文件数目:%d\n", countfile);
    printf("========================\n");

    return 0;
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