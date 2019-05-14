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

struct info {
    char filename[256];
    struct stat stat;
};

struct info *list(char[], struct info infos[]);
struct info getStat(char *);

long cmpBySize (struct info *a, struct info *b);
long cmpByDate (struct info *a, struct info *b);
void printDefalt();
void printBySize();
void printByDate();

struct info infos[256]; // 定义 struct info 类型的数组用来存放 info 结构体。
int countdir = 0;
int countfile = 0;

struct info *list(char dirname[], struct info infos[]) {

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

        struct info this_info = getStat(s); 
        infos[infos_index] = this_info;
        infos_index++; 
    }

    closedir(dir_ptr);
    return infos;
}

struct info getStat(char *filename) {
    struct info info;
    strcpy(info.filename, filename);
    if (stat(filename, &info.stat) == -1) {
        perror(filename);
    } else {
        return info;
    }
}

void printDefault() {
    for (int i = 0; strlen(infos[i].filename) > 0; ++i) {
        printf("%12ld    ", (long)infos[i].stat.st_size);
        printf("%.24s    ", ctime(&infos[i].stat.st_mtime));  
        printf("%s", infos[i].filename);
        printf("\n");   
    }

}

void printBySize() {
    qsort(infos, countdir + countfile, sizeof(struct info), cmpBySize);
    printDefault();

}

void printByDate() {
    qsort(infos, countdir + countfile, sizeof(struct info), cmpByDate);
    printDefault();
}


long cmpBySize (struct info *a, struct info *b) {
   return ((*a).stat.st_size - (*b).stat.st_size);
}

long cmpByDate (struct info *a, struct info *b) {
    return ((*a).stat.st_mtime - (*b).stat.st_mtime);
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