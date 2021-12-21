#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define usl_op(x) (((x)=='+')||((x)=='-')||((x)=='*')||((x)=='/'))
#define usl_no ((C!='+')&&(C!='-')&&(C!='*')&&(C!='/')\
&&(C!='(')&&(C!=')'))

typedef struct Poliz{
    int size;
    char *data;
} Poliz;

typedef void (*calcul_elem) (const void *p, int k);

typedef struct Perem{
    char s[7];
    int n;
    struct Perem *next;
} Perem;

typedef struct Stek{
    int n;
    struct Stek *prev;
} Stek;

typedef struct elem_perem{
    void *f;
    char s[7];
} elem_perem;

typedef struct elem_chyslo{
    void *f;
    int k;
} elem_chyslo;

typedef struct elem_oper{
    void *f;
    char c;
} elem_oper;

Poliz *poliz=NULL;
Perem *perem=NULL;
Stek *stek=NULL;
char C;
int K=0, V=0;

void func1(void);
void func2(void);
void func3(void);
int add_perem(char *s);
int prov_per(void);
int add_poliz(const void *elem, int size);
int sravn(char *s);
void push_perem(const void*p, int k);
void error_exit(void);
void delete_perem(void);
void delete_poliz(void);

void nextchar(void){
    C = (char) getchar();
    if ((C == ' ') && (K == 3)){
        K = 4;
    }
    while (C == ' ')
        C = (char) getchar();
    if (!usl_op(C) && (K==4)){
        fprintf(stderr, "error, variable writing or number!\n");
        error_exit();
    }
    if (C == ')'){
        if (V == 0) {
            fprintf(stderr,
                    "error,  out of balance between brackets!\n");
            error_exit();
        } else V--;
    }
    if (usl_op(C))
        if (K == 1){
            fprintf(stderr, "error, 2 operations in a row!\n");
            error_exit();
        } else {
            K = 1;
        }
    else if (C == '('){
        K = 2;
    } else if ((C == ')')&&(K==2)){
        fprintf(stderr, "error, 2 brackets in a row!\n");
        error_exit();
    } else K = 0;
    if (usl_no && prov_per() && (C != '\n') && (C != EOF)){
        fprintf(stderr, "%c: error, unknown symbol!\n",
                C);
        error_exit();
    }
}

void error_exit(void){
    delete_perem();
    delete_poliz();
    Stek *list, *list1=stek;
    if (stek != NULL){
    	while (list1 != NULL){
    	    list = list1;
    	    list1 = list->prev;
    	    list->prev = NULL;
    	    free(list);
    	}
    }
    exit(-1);
}

int prov_per(void){
    if (((C < 'a')||(C > 'z')) &&
    ((C < 'A')||(C > 'Z')) &&
    ((C < '0')||(C > '9')) && (C != '_'))
        return 1;
    return 0;
}

int prov_num(void){
    if ((C < '0')||(C > '9'))
        return 1;
    return 0;
}

int number(void){
    char s[15];
    int i = 0;
    while ((C != ' ') && usl_no && (C != '\n')){
        if (prov_num()){
            fprintf(stderr, "error, writing number!\n");
            error_exit();
        }
        s[i] = C;
        i++;
        K = 3;
        nextchar();
    }
    return atoi(s);
}

void per(void){
    char s[7];
    int i = 0;
    while ((C != ' ') && (i < 6) && usl_no && (C != '\n')){
        if (prov_per()){
            fprintf(stderr, "error, variable writing!\n");
            error_exit();
        }
        s[i] = C;
        i++;
        K = 3;
        nextchar();
    }
    s[i]='\0';
    int b = i;
    add_perem(s);
    if ((i == 6) && (C != ' ') && (C != '\n') && usl_no){
        fprintf(stderr, "error, variable writing!\n");
        error_exit();
    }
    elem_perem *p = NULL;
    p = malloc(sizeof(elem_perem));
    p->f = push_perem;
    for (int j = 0; j < 7; j++) {
        p->s[j] = s[j];
    }
    char *s1;
    s1 = malloc(sizeof(p->f)+b);
    memcpy(s1, p, sizeof(p->f));
    memcpy(&s1[sizeof(p->f)], p->s, b);
    add_poliz(s1, sizeof(p->f) + b);
    free(p);
    free(s1);
}

void write_poliz(void){
    printf("%d\n", poliz->size);
    if (poliz != NULL) {
        int a = (int) poliz->data[0];
        printf("%d", a);
        putchar(poliz->data[5]);
        //putchar(poliz->data[7]);
        int a1 = (int) poliz->data[6];
        printf("%d", a1);
        putchar(poliz->data[11]);
        //putchar(poliz->data[15]);
        int a2 = (int) poliz->data[12];
        printf("%d", a2);
        putchar(poliz->data[17]);
        //putchar(poliz->data[23]);
        int a3 = (int) poliz->data[18];
        printf("%d", a3);
        putchar(poliz->data[23]);
        int a4 = (int) poliz->data[24];
        printf("%d", a4);
        putchar(poliz->data[29]);
        int a5 = (int) poliz->data[30];
        printf("%d", a5);
        putchar(poliz->data[35]);
        int a6 = (int) poliz->data[36];
        printf("%d", a6);
        putchar(poliz->data[41]);
        putchar('\n');
    }
}

void write_perem(void){
    Perem *list=perem;
    while (list!=NULL){
        printf("%s = ", list->s);
        printf("%d\n", list->n);
        list=list->next;
    }
}

void write_stek(void){
    Stek *list=stek;
    while (list!=NULL){
        printf("%d, ", list->n);
        list=list->prev;
    }
    putchar('\n');
}

void vvod_perem(void){ 
    if (perem ==NULL){
        fprintf(stderr, "error entering values for variables!\n");
        error_exit();
    }
    char s[258], s1[258], s2[7], *s_pr;
    const char st[6]="stop\n\0";
    printf("vvod perem:\n");
    while (strcmp(s, st)){
        s_pr = fgets(s, 256, stdin);
        if(s_pr==NULL) s_pr = NULL;
        if(!strcmp(s, st)) {
            continue;
        }
        char *c = strchr(s, '=');
        if (c == NULL){
            printf("error entering values for variables1!\n");
            continue;
        }
        int k = (int) (c - s + 1);
        if (!k || (k>=8) || (s[k] != ' ')) {
            printf("error entering values for variables2!\n");
            continue;
        }
        int i;
        for(i=0; i<(k-1); i++)
            s2[i]= s[i];
        s2[i-1]='\0';
        int b = 1;
        if ((s[k+1]!='-') && (s[k+1] > '9') && (s[k+1] < '0')){
        	b = 0;
        }
        for(int j=k+2; j<strlen(s)-1; j++) {
            if (sravn(s2) || (s[j] > '9') || (s[j] < '0')) {
                printf("error entering values for variables3!\n");
                b = 0;
                break;
            }
        }
        Perem* list=perem;
        while((list!=NULL) && strcmp(s2, list->s)){
            list=list->next;
        }
        strcpy(s1, &s[k+1]);
        if ((list == NULL) && (b)){
            printf("error entering values for variables4!\n");
            continue;
        }
        if (b) list->n = atoi(s1);
    }
}

void push(const void *p, int k){
    int n =  *((int*)p);
    Stek* list=NULL;
    list = malloc(sizeof(Stek));
    list->n = n;
    list->prev = stek;
    stek = list;
}

int pop(void){
    Stek* list=stek;
    if (list == NULL){
        fprintf(stderr, "stek handling error!\n");
        error_exit();
    }
    int k = list->n;
    stek = list->prev;
    list->prev = NULL;
    free(list);
    return k;
}

void push_perem(const void *p, int k){
    char *s = (char*)p;
    Perem *list=perem;
    char s1[7];
    int a=0;
    while ((a == 0)||(a == 2)) {
        if(a!=0) list=list->next;
        a = 1;
        int i;
        for (i=0; i < k; i++){
            	s1[i]=*(s+i);
            }
        s1[k] = '\0';
        if (strcmp(s1, list->s)) a = 2;
    }
    push(&list->n, 0);
}

void oper(const void *p, int k){
    char c = *((char*)p);
    int a1, a2, a;
    a1 = pop();
    a2 = pop();
    if (c == '+') a = a1 + a2;
    if (c == '-') a = a2 - a1;
    if (c == '*') a = a1 * a2;
    if (c == '/') {
        if (a1 == 0){
            fprintf(stderr, "error, division by 0!\n");
            error_exit();
        }
        a = a2 / a1;
    }
    push(&a, 0);
}

void delete_poliz(void){
    poliz->data=realloc(poliz->data, sizeof(char));
    free(poliz->data);
    free(poliz);
}

void delete_stek(void){
    if (stek == NULL){
        fprintf(stderr, "expression evaluation error!\n");
        error_exit();
    }
    if (stek->prev != NULL){
        fprintf(stderr, "expression evaluation error!\n");
        error_exit();
    }
    free(stek);
}

Perem* new_perem(const char *s){
    Perem* list=NULL;
    list = malloc(sizeof(Perem));
    for(int i=0; i<7; i++)
        list->s[i] = s[i];
    list->n = 0;
    list->next = NULL;
    return list;
}

int sravn(char *s){
    Perem* list=perem;
    while (list != NULL){
        if (strcmp(list->s, s) == 0)
            return 0;
        list = list->next;
    }
    return 1;
}

int add_perem(char *s){
    if (perem == NULL){
        perem = new_perem(s);
    } else {
        if (sravn(s)){
            Perem* list=perem;
            while (list->next != NULL)
                list = list->next;
            list->next= new_perem(s);
        }
    }
    return 0;
}

void delete_perem(void){
    if (perem != NULL) {
        Perem *list1, *list = perem;
        while (list != NULL) {
            list1 = list->next;
            list->next = NULL;
            free(list);
            list = list1;
        }
        perem = NULL;
    }
}

int calculate_polis(void){
    int i = 0;
    int x;
    calcul_elem p;
    void *p1;
    if (poliz->size == 0) return 1;
    while (i<poliz->size){
        x = (int) poliz->data[i];
        p1 = malloc(x-sizeof(calcul_elem));
        memcpy(&p, &poliz->data[i+1], sizeof(calcul_elem));
        memcpy(p1, &poliz->data[i+1+sizeof(calcul_elem)], x-sizeof(calcul_elem));
        p(p1, x-sizeof(calcul_elem));
        i+= x+1;
        free(p1);
    }
    printf("%d\n", stek->n);
    return 0;
}

int add_poliz(const void *elem, int size){
    if (poliz->size == 0) {
        poliz->data = (char*) malloc(sizeof(char)*(size+1));
        poliz->size += size+1;
    } else {
        poliz->size += size+1;
        poliz->data = (char *) realloc(poliz->data, sizeof(char) * (poliz->size));
    }
    if (poliz->data == NULL){
        return 1;
    }
    char a = (char) size;
    ((char*)poliz->data)[poliz->size - size - 1] = a;
    for (int i = 0; i < size; i++){
        ((char*)poliz->data)[poliz->size - size + i] = ((char*)elem)[i];
    }
    return 0;
}

void add_op_pol(char c){
    elem_oper *p = NULL;
    p = malloc(sizeof(elem_oper));
    p->f = oper;
    p->c = c;
    char *s1;
    s1 = malloc(sizeof(p->f)+sizeof(p->c));
    memcpy(s1, p, sizeof(p->f));
    s1[sizeof(p->f)] = c;
    add_poliz(s1, sizeof(p->f)+sizeof(p->c));
    free(p);
    free(s1);
}

void add_ch_pol(int k){
    elem_chyslo *p = NULL;
    p = malloc(sizeof(elem_chyslo));
    p->f = push;
    p->k = k;
    char *s1;
    s1 = malloc(sizeof(p->f)+sizeof(p->k));
    memcpy(s1, p, sizeof(p->f));
    memcpy(&s1[sizeof(p->f)], &k, sizeof(p->k));
    add_poliz(s1, sizeof(p->f)+sizeof(p->k));
    free(p);
    free(s1);
}

void func1(void) {
    func2();
    while(C=='+' || C=='-') {
        char temp = C;
        nextchar();
        func2();
        add_op_pol(temp);
    }
}

void func2(void) {
    func3();
    while(C=='*' || C=='/') {
        char temp = C;
        nextchar();
        func3();
        add_op_pol(temp);
        }
}

void func3(void) {
    if(C=='(') {
        nextchar();
        V++;
        func1();
        if(C!=')') {
            fprintf(stderr, "error,  out of balance between brackets!\n");
            error_exit();
        } else {
        	nextchar();
               if (C == '('){
                   fprintf(stderr, "error,  )(!\n");
            	    error_exit();
               }
        }
    } else {
        if (C == '_'){
            fprintf(stderr, "error, variable writing!\n");
            error_exit();
        }
        if (((C >= 'a') && (C <= 'z')) ||
        ((C <= 'Z') && (C >= 'A'))){
            per();
        }
        if ((C >= '0') && (C <= '9')){
            int k = number();
            add_ch_pol(k);
        }
    }
}

int main(void){
    poliz = malloc(sizeof(Poliz));
    poliz->size=0;
    nextchar();
    func1();
    vvod_perem();
    calculate_polis();
    delete_perem();
    delete_poliz();
    delete_stek();
    return 0;
}
