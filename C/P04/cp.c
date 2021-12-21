#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const char s_err[24]="error: wrong arguments\n\0";

int main(int argc, char **argv){
    char buf[1024];
    int fd1, fd2, n;
    if (argc != 3) {
        if(write(2, s_err, 23) < 23){
            return(-2);
        }
        return -1;
    }
    struct stat s;
    if ((fd1 = open(argv[1], O_RDONLY))==-1){
        if(write(2, s_err, 23) < 23){
            return(-2);
        }
        return -1;
    }
    stat(argv[1], &s);
    if ((fd2 = open(argv[2], O_RDONLY))!=-1){
        if(write(2, s_err, 23) < 23){
            return(-2);
        }
        return -1;
    }
    if ((fd2 = creat(argv[2], s.st_mode))==-1){
        if(write(2, s_err, 23) < 23){
            return(-2);
        }
        return -1;
    }
    while ((n = read(fd1, buf, 1024))>0)
        if(write(fd2, buf, n) < n){
            return(-2);
        }
    return 0;
}
