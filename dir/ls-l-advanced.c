#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>

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
    if (argc == 1) {
        list(".");
    } else {
        while (--argc) { 
            printf("%s:\n", *(++argv));
            list(*argv);
        }
    }
    
    return 0;
}


/*
~/w/ccnu-unix   *…  dir  ./a.out /Users/qianqian/work/ccnu-unix
/Users/qianqian/work/ccnu-unix:
         288    Thu May  9 09:38:13     /Users/qianqian/work/ccnu-unix/.
         960    Sat Mar 30 00:15:12     /Users/qianqian/work/ccnu-unix/..
        1064    Thu Mar 28 00:15:55     /Users/qianqian/work/ccnu-unix/LICENSE
         128    Thu Apr 25 08:23:07     /Users/qianqian/work/ccnu-unix/shell
          56    Thu Mar 28 00:15:55     /Users/qianqian/work/ccnu-unix/README.md
         320    Thu Apr 25 09:22:36     /Users/qianqian/work/ccnu-unix/p1p2
         224    Sat May 11 01:00:27     /Users/qianqian/work/ccnu-unix/dir
         448    Sat May 11 00:00:09     /Users/qianqian/work/ccnu-unix/.git
         128    Thu Mar 28 14:07:00     /Users/qianqian/work/ccnu-unix/合法标识符
========================
文件夹数目:7
文件数目:2 */
