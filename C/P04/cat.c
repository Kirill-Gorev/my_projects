#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

const char s_flag[3]="-n\0";
const char s_err[24]="error: wrong arguments\n\0";
const int N = 4096;
int nom = 0;

int prov_con(char *s, int n){
    int k = 0;
    while((s[k] != '\n')&&(k<n))
        k++;
    if (s[k]!='\n') return n+1;
    return k+1;
}

int vyvod(int fd, int k){
    char buf[N+1], *str=NULL;
    int n, pos = 0;
    while((n=read(fd, buf, N))>0){
        int sdv = 0, nm;
        buf[n]= '\0';
        str= (char*) malloc(sizeof(char)*(n+1));
        str[sizeof(char)*n]='\0';
        nm = prov_con(buf, n);
        buf[nm] = '\0';
        strcpy(str, buf);
        if (nm == n+1) sdv = N;
        else pos += nm;
        while((nm == n+1) && (n=read(fd, buf, N))>0){
            sdv += n;
            str = (char*) realloc(str, sizeof(char)*(sdv+1));
            nm = prov_con(buf, n);
            buf[nm] = '\0';
            strcpy(&str[sdv - n], buf);
            if (nm != n+1){ 
                sdv = sdv - n + nm;
                str = (char*) realloc(str, sizeof(char)*(sdv));
            }
        }
        if (k){
            nom++;
            int l= sprintf(buf, "%d", nom);
            if(write(1, buf, l) < l){
                exit(2);
            }
            buf[0]=' ';
            buf[1]=' ';
            if(write(1, buf, 2) < 2){
                exit(2);
            }
        }
        if(write(1, str, strlen(str)) < strlen(str)){
            exit(2);
        }
        pos += sdv;
        lseek(fd, pos, SEEK_SET);
        free(str);
    }
    return 0;
}

int main(int argc, char **argv){
    int fd, k = 0;
    if (argc<2) {
        if(write(2, s_err, 23) < 23){
            exit(2);
        }
        return 1;
    }
    if (!strcmp(argv[1], s_flag)) k = 1;
    for(int i=k; i<argc-1; i++){
    	if ((fd = open(argv[i+1], O_RDONLY)) == -1) {
            if(write(2, s_err, 23) < 23){
                exit(2);
            }
            return 1;
        }
        vyvod(fd, k);
        close(fd);
    }
    return 0;
}
