#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

void list(char[]);
void getStat(char *);
void show_file_info(char *,struct stat*);


void list(char dirname[]) {

    DIR *dir_ptr;
    struct dirent *direntp;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "error message: %s \n", strerror(errno));
    }
 
    while ((direntp = readdir(dir_ptr)) != NULL){
        getStat(direntp->d_name); 
    }

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

// ~/w/ccnu-unix$ ./a.out
//         192    Fri May 10 22:46:50     .
//         288    Thu May  9 09:38:13     ..
//        1606    Fri May 10 22:46:26     ls-l.c
//         664    Thu May  9 09:40:11     dirName.c
//        9084    Fri May 10 22:46:50     a.out
//        2281    Thu May  9 12:25:04     struct_stat.c
