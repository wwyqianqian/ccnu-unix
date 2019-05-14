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

struct stat *list(char[], struct stat infos[]);
struct stat getStat(char *);
void show_file_info(char *,struct stat*);
long cmpBySize (struct stat *a, struct stat *b);

struct stat infos[256]; // 定义 struct stat 类型的数组用来存放 info 结构体。

struct stat *list(char dirname[], struct stat infos[]) {

    DIR *dir_ptr;
    struct dirent *direntp;
    int countdir = 0;
    int countfile = 0;

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

    printf("========================\n");
    printf("文件夹数目:%d\n", countdir);
    printf("文件数目:%d\n", countfile);

    closedir(dir_ptr);
    return infos;
}

void printDefalt(struct stat *infos) {
    printf("%12ld    ", (long)infos->st_size);
    printf("%.19s     ", ctime(&infos->st_mtime));
    // printf("%s\n", filename);
}


long cmpBySize (struct stat *a, struct stat *b) {
   return (a->st_size - b->st_size);
}



struct stat getStat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename);
    } else {
        // show_file_info(filename, &info);
        return info;
    }
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
        list(argv[optind], infos);
        printDefalt(infos);
    } else { 
        list(".", infos);
    }

}








    // qsort(infos, countdir+countfile, sizeof(struct stat), cmpBySize);
    // printf("%lld\n", infos[0].st_size);
    // printf("%lld\n", infos[1].st_size);
    // printf("%lld\n", infos[2].st_size);
    // printf("%lld\n", infos[3].st_size);
    // printf("%lld\n", infos[4].st_size);

// void show_file_info(char *filename, struct stat *info_p) {
    

//     printf("%12ld    ", (long)info_p->st_size);
//     printf("%.19ld     ", info_p->st_mtime);
//     printf("%s\n", filename);
// }

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