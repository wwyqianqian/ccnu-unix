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

        getStat(direntp->d_name); 
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


/*         224    Fri May 10 23:56:37     .
         288    Thu May  9 09:38:13     ..
        1535    Fri May 10 22:47:53     ls-l.c
         664    Thu May  9 09:40:11     dirName.c
        9084    Fri May 10 23:56:37     a.out
        2281    Thu May  9 12:25:04     struct_stat.c
        2115    Fri May 10 23:56:30     ls-l-advanced.c
========================
文件夹数目:2
文件数目:5 */
