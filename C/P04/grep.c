#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

const char s_flag[3]="-v\0";
const char s_err[24]="error: wrong arguments\n\0";
const char s_wr[14]="error: write\n\0";
const int N = 4096;

int podstr(char *s, char *s_p, int len_p, int len_s){
    int i = 0;
    while(i <len_s-len_p+1){
        int f = 1;
        for(int j=0; j<len_p; j++){
            if (s[j+i] != s_p[j]){
            	f = 0;
            	break;
            }
        }
        if (f) return 1;
        i++;
    }
    return 0;
}

int prov_con(char *s, int n){
    int k = 0;
    while((s[k] != '\n')&&(k<n))
        k++;
    if (s[k]!='\n') return n+1;
    return k+1;
}

int poisk(int k, char **argv){
    char buf[N+1], *str=NULL;
    int fd, n, len= 0, pos = 0;
    while (argv[1+k][len] != '\0')
    	len++;
    if ((fd = open(argv[2+k], O_RDONLY)) == -1) {
        if(write(2, s_err, 23) < 23){
            exit(2);
        }
        return -1;
    }
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
        if (podstr(str, argv[1+k], len, strlen(str)) ^ k)
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
    int k = 0;
    if (argc < 3){
        if(write(2, s_err, 23) < 23){
            exit(2);
        }
        return 1;
    }
    if (!strcmp(argv[1], s_flag)) k = 1;
    if (argc > 3+k){
        if(write(2, s_err, 23) < 23){
            exit(2);
        }
        return 1;
    }
    if (poisk(k, argv)) return 1;
    return 0;
}
