// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /*device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for filesystem I/O */
//     blkcnt_t  st_blocks;  /* number of blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };


#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

prntimes(struct stat *stbuf) {
    char *time;
    printf("last access: %s", ctime(&stbuf->st_atime));
    printf("last modification: %s", ctime(&stbuf->st_mtime));
    printf("last status change: %s", ctime(&stbuf->st_ctime));
}

int main(int argc, char const *argv[]) {
    struct stat stbuf;

    if (stat(argv[1], &stbuf) == -1) {
        perror(argv[1]);
        exit(1);
    }

    printf("file name: %s \n", argv[1]);
    printf("device: %d \n", stbuf.st_dev);
    printf("i-num: %u\n", stbuf.st_ino);
    printf("links: %d\n", stbuf.st_nlink);
    printf("file size: %ld\n", stbuf.st_size);

    prntimes(&stbuf);
    return 0;
}


//  ~/Desktop$  ./a.out /Users/qianqian/work/ccnu-unix/p1p2

// file name: /Users/qianqian/work/ccnu-unix/p1p2
// device: 16777220
// i-num: 24587201
// links: 10
// file size: 320
// last access: Thu May  9 11:32:17 2019
// last modification: Thu Apr 25 09:22:36 2019
// last status change: Thu Apr 25 09:22:36 2019


// 验证 320:
//  ~/w/ccnu-unix$ ls -lh         Thu May  9 11:47:14 2019
// total 16
// -rw-r--r--   1 qianqian  staff   1.0K Mar 28 00:15 LICENSE
// -rw-r--r--   1 qianqian  staff    56B Mar 28 00:15 README.md
// drwxr-xr-x   3 qianqian  staff    96B May  9 09:40 dir
// drwxr-xr-x  10 qianqian  staff   320B Apr 25 09:22 p1p2
// drwxr-xr-x   4 qianqian  staff   128B Apr 25 08:23 shell
// drwxr-xr-x   4 qianqian  staff   128B Mar 28 14:07 合法标识符