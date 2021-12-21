#include <iostream>
#include "matrix.hpp"
using namespace std;

List::List(double value, size_t n): a(value), n_pillars(n), next(nullptr),
        prev(nullptr){}
StringMatrix::StringMatrix(): string(nullptr){}
double & StringMatrix::operator [](size_t k){
    size_t n = k - 1;
    List *p = string, *p_pr = nullptr;
    if (p == nullptr){
        string = new List(0, n);
        double &b = string->a;
        return b;
    }
    while(p->n_pillars < n){
        p_pr = p;
        p = p->next;
        if (p == nullptr) break;
    }
    if(p == nullptr){
        p = new List(0, n);
        p_pr->next = p;
        p->prev = p_pr;
        double &b = p->a;
        return b;
    }
    if(p->n_pillars == n){
        double &b = p->a;
        return b;
    }
    List *p2;
    p2 = new List(0, n);
    if(p_pr != nullptr) p_pr->next = p2;
    else string = p2;
    p2->prev = p_pr;
    p2->next = p;
    p->prev = p2;
    double &b = p2->a;
    return b;
}

double StringMatrix::operator [] (size_t k) const{
    size_t n = k - 1;
    List *p = string;
    if (p == nullptr){
        return 0;
    }
    while(p->n_pillars < n){
        p = p->next;
        if (p == nullptr) break;
    }
    if(p == nullptr){
        return 0;
    }
    if(p->n_pillars == n){
        return p->a;
    }
    return 0;
}

double* StringMatrix::operator+(size_t k){
    size_t n = k - 1;
    List *p = string, *p_pr = nullptr;
    if (p == nullptr){
        string = new List(0, n);
        double *b = &(string->a);
        return b;
    }
    while(p->n_pillars < n){
        p_pr = p;
        p = p->next;
        if (p == nullptr) break;
    }
    if(p == nullptr){
        p = new List(0, n);
        p_pr->next = p;
        p->prev = p_pr;
        double *b = &(p->a);
        return b;
    }
    if(p->n_pillars == n){
        double *b = &(p->a);
        return b;
    }
    List *p2;
    p2 = new List(0, n);
    if(p_pr != nullptr) p_pr->next = p2;
    else string = p2;
    p2->prev = p_pr;
    p2->next = p;
    p->prev = p2;
    double *b = &(p2->a);
    return b;
}

const double* StringMatrix::operator + (size_t k) const{
    size_t n = k - 1;
    List *p = string;
    if (p == nullptr){
        const double *b = &(Znach);
        return b;
    }
    while(p->n_pillars < n){
        p = p->next;
        if (p == nullptr) break;
    }
    if(p == nullptr){
        const double *b = &(Znach);
        return b;
    }
    if(p->n_pillars == n){
        const double *b = &(p->a);
        return b;
    }
    const double *b = &(Znach);
    return b;
}

StringMatrix::StringMatrix(StringMatrix const &str){
    if(str.string == nullptr) string = nullptr;
    else{
        List *p = str.string;
        size_t k = 0;
        while(p != nullptr){
            k++;
            p = p->next;
        }
        string = new List(str.string->a, str.string->n_pillars);
        List *p1 = string;
        List *p2 = str.string;
        for(size_t i = 1; i < k; i++){
            p2 = p2->next;
            p = new List(p2->a, p2->n_pillars);
            p1->next = p;
            p->prev = p1;
            p1 = p;
        }
    }
}
void StringMatrix:: delete_List(){
    List *p = string;
    List *p1 = nullptr;
    if(p != nullptr){
        p1 = p->next;
        while(p->next != nullptr){
            p1 = p->next;
            p1->prev = nullptr;
            p->next = nullptr;
            delete p;
            p = p1;
        }
        delete p1;
    }
    string = nullptr;
}
double StringMatrix::get(size_t b) const{
    size_t n = b - 1;
    List *p = string;
    if(p == nullptr) return 0.0;
    while(p->n_pillars < n){
        p = p->next;
        if (p == nullptr) break;
    }
    if(p == nullptr) return 0.0;
    if(p->n_pillars == n) return p->a;
    return 0.0;
}
bool StringMatrix::operator !=(StringMatrix const &str) const{
    bool fl = false;
    if((string == nullptr) && (str.string == nullptr)) return false;
    if((string == nullptr) && (str.string != nullptr)) return true;
    if((string != nullptr) && (str.string == nullptr)) return true;
    List *p1 = string, *p2 = str.string;
    size_t k1 = 0, k2 = 0;
    while(p1 != nullptr){
        k1++;
        p1 = p1->next;
    }
    while(p2 != nullptr){
        k2++;
        p2 = p2->next;
    }
    if(k1 != k2) return true;
    p1 = string;
    p2 = str.string;
    for(size_t i = 0; i < k1; i++){
        if(((p1->a - p2->a) >= E) || (p1->n_pillars != p2->n_pillars))
            return true;
        p1 = p1->next;
        p2 = p2->next;
    }
    return fl;
}
bool StringMatrix::operator ==(StringMatrix const &str) const{
    bool fl = true;
    if((string == nullptr) && (str.string == nullptr)) return true;
    if((string == nullptr) && (str.string != nullptr)) return false;
    if((string != nullptr) && (str.string == nullptr)) return false;
    List *p1 = string, *p2 = str.string;
    size_t k1 = 0, k2 = 0;
    while(p1 != nullptr){
        k1++;
        p1 = p1->next;
    }
    while(p2 != nullptr){
        k2++;
        p2 = p2->next;
    }
    if(k1 != k2) return false;
    p1 = string;
    p2 = str.string;
    for(size_t i = 0; i < k1; i++){
        if(((p1->a - p2->a) >= E) || (p1->n_pillars != p2->n_pillars))
            return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return fl;
}
StringMatrix& StringMatrix::operator= (StringMatrix const &str){
    if(str.string == nullptr) string = nullptr;
    else{
        List *p = str.string;
        size_t k = 0;
        while(p != nullptr){
            k++;
            p = p->next;
        }
        string = new List(str.string->a, str.string->n_pillars);
        List *p1 = string;
        List *p2 = str.string;
        for(size_t i = 1; i < k; i++){
            p2 = p2->next;
            p = new List(p2->a, p2->n_pillars);
            p1->next = p;
            p->prev = p1;
            p1 = p;
        }
    }
    return *this;
}
StringMatrix& StringMatrix::operator+ (StringMatrix const &str) const{
    StringMatrix *Val_s;
    Val_s = new StringMatrix(*this);
    List *p1 = Val_s->string;
    List *p2 = str.string;
    List *p_pr = nullptr;
    while((p1 != nullptr) || (p2 != nullptr)){
        if(p1 == nullptr){
            while(p2 != nullptr){
                List *l = new List(p2->a, p2->n_pillars);
                if(p_pr != nullptr) p_pr->next = l;
                else Val_s->string = l;
                l->prev = p_pr;
                p_pr = l;
                p2 = p2->next;
            }
            return *Val_s;
        }
        if(p2 == nullptr) {
            return *Val_s;
        }
        if(p1->n_pillars == p2->n_pillars){
            p1->a += p2->a;
            p_pr = p1;
            p1 = p1->next;
            p2 = p2->next;
            continue;
        }
        if(p1->n_pillars > p2->n_pillars){
            List *l = new List(p2->a, p2->n_pillars);
            List *p = p1->prev;
            p->next = l;
            p1->prev = l;
            l->next = p1;
            l->prev = p;
            p2 = p2->next;
            continue;
        }
        if(p1->n_pillars < p2->n_pillars){
            p_pr = p1;
            p1 = p1->next;
            continue;
        }
    }
    return *Val_s;
}
StringMatrix::~StringMatrix(){
    delete_List();
}

SparseMatrix::SparseMatrix(size_t a, size_t b): string(a), pillars(b){
    copy_m = nullptr;
    matrix = new StringMatrix*[a];
    for(size_t i = 0; i < a; i++)
        matrix[i] = new StringMatrix;
}
SparseMatrix::SparseMatrix(SparseMatrix &M){
    pillars = M.pillars;
    string = M.string;
    matrix = new StringMatrix*[string];
    copy_m = nullptr;
    for(size_t i = 0; i < string; i++){
        StringMatrix &M1 = *(M.matrix[i]);
        matrix[i] = new StringMatrix(M1);
    }
}
StringMatrix& SparseMatrix::operator [](size_t k){
    if((k > string) || (k < 1)){
        cout << "Error operator []" << endl;
        exit(1);
    }
    return *(matrix[k-1]);
}
const StringMatrix& SparseMatrix::operator [] (size_t k) const{
    if((k > string) || (k < 1)){
        cout << "Error operator []" << endl;
        exit(1);
    }
    return *(matrix[k-1]);
}
double SparseMatrix::get(size_t a, size_t b) const{
    if((a > string) || (a < 1) || (b > pillars) || (b < 1)){
        cout << "Error method get" << endl;
        exit(1);
    }
    if (matrix[a-1] == nullptr) return 0.0;
    double val = matrix[a - 1]->get(b);
    return val;
}
void SparseMatrix::set(size_t a, size_t b, double val) {
    if((a > string) || (a < 1) || (b > pillars) || (b < 1)){
        cout << "Error method get" << endl;
        exit(1);
    }
    (*(matrix[a - 1]))[b] = val;
}
size_t SparseMatrix::num_rows() const {return string;}
size_t SparseMatrix::num_collums() const {return pillars;}
SparseMatrix::~SparseMatrix(){
    if(copy_m != nullptr){
        copy_m->~SparseMatrix();
        copy_m = nullptr;
    }
    for(size_t i = 0; i < string; i++) {
        if (matrix[i] != nullptr) matrix[i]->~StringMatrix();
        delete matrix[i];
    }
    delete [] matrix;
}
bool SparseMatrix::operator ==(SparseMatrix const &M) const{
    bool fl = true;
    if((string != M.string) || (pillars != M.pillars))
        return false;
    for(size_t i = 0; i < string; i++) {
        if (*(matrix[i]) != *(M.matrix[i])) {
            fl = false;
            break;
        }
    }
    return fl;
}
bool SparseMatrix::operator !=(SparseMatrix const &M) const{
    bool fl = false;
    if((string != M.string) || (pillars != M.pillars))
        return true;
    for(size_t i = 0; i < string; i++) {
        if (*(matrix[i]) != *(M.matrix[i])) {
            fl = true;
            break;
        }
    }
    return fl;
}
SparseMatrix& SparseMatrix::operator= (SparseMatrix const &M) {
    for(size_t i = 0; i < string; i++){
        matrix[i]->~StringMatrix();
    }
    delete [] matrix;
    matrix = new StringMatrix*[M.string];
    pillars = M.pillars;
    string = M.string;
    copy_m = nullptr;
    for(size_t i = 0; i < M.string; i++)
        matrix[i] = new StringMatrix;
    for(size_t i = 0; i < string; i++){
        *(matrix[i]) = *(M.matrix[i]);
    }
    return *this;
}
SparseMatrix& SparseMatrix::operator+ (SparseMatrix const &M){
    if(copy_m != nullptr){
        copy_m->~SparseMatrix();
        copy_m = nullptr;
    }
    if((M.string != string) || (M.pillars != pillars)){
        cout << "Error operator +" << endl;
        exit(1);
    }
    SparseMatrix *Val_M;
    Val_M = new SparseMatrix(*this);
    copy_m = Val_M;
    for(size_t i = 0; i<string; i++)
        *(Val_M->matrix[i]) = *(Val_M->matrix[i]) + *(M.matrix[i]);
    return *Val_M;
}
StringMatrix* SparseMatrix::operator+ (size_t k){
    if((k > string) || (k < 1)){
        cout << "Error operator +" << endl;
        exit(1);
    }
    return matrix[k-1];
}
const StringMatrix* SparseMatrix::operator + (size_t k) const{
    if((k > string) || (k < 1)){
        cout << "Error operator +" << endl;
        exit(1);
    }
    return matrix[k-1];
}
SparseMatrix& SparseMatrix::operator* (SparseMatrix const &M){
    if(copy_m != nullptr){
        copy_m->~SparseMatrix();
        copy_m = nullptr;
    }
    if(M.string != pillars){
        cout << "Error operator *" << endl;
        exit(1);
    }
    SparseMatrix *Val_M;
    Val_M = new SparseMatrix(string, M.pillars);
    copy_m = Val_M;
    for (size_t i = 1; i < string + 1; i++)
        for (size_t j = 1; j < M.pillars + 1; j++) {
            double Sum = 0;
            for (size_t k = 1; k < pillars + 1; k++)
                Sum += (this->get(i, k) * M.get(k, j));
            if((Sum - 0.0) >= E) (*(Val_M->matrix[i-1]))[j] = Sum;
        }
    return *Val_M;
}
