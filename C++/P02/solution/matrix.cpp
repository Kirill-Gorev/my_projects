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
    List *p1 = p;
    if(p != nullptr){
        p1 = p->next;
        while(p->next != nullptr){
            p1->prev = nullptr;
            p->next = nullptr;
            delete p;
            p = p1;
            p1 = p->next;
        }
        delete p;
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
    return !(*this != str);
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
        if(this != &str) delete [] string;
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
List* StringMatrix::elem_row() const{
    return string;
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
#define Realization_Matrix(T)\
T::T(T &M){\
    pillars = M.pillars;\
    string = M.string;\
    matrix = new StringMatrix*[string];\
    copy_m = nullptr;\
    for(size_t i = 0; i < string; i++){\
        StringMatrix &M1 = *(M.matrix[i]);\
        matrix[i] = new StringMatrix(M1);\
    }\
}\
StringMatrix& T::operator [](size_t k){\
    if((k > string) || (k < 1)){\
        cout << "Error operator []" << endl;\
        exit(1);\
    }\
    return *(matrix[k-1]);\
}\
const StringMatrix& T::operator [] (size_t k) const{\
    if((k > string) || (k < 1)){\
        cout << "Error operator []" << endl;\
        exit(1);\
    }\
    return *(matrix[k-1]);\
}\
double T::get(size_t a, size_t b) const{\
    if((a > string) || (a < 1) || (b > pillars) || (b < 1)){\
        cout << "Error method get" << endl;\
        exit(1);\
    }\
    if (matrix[a-1] == nullptr) return 0.0;\
    double val = matrix[a - 1]->get(b);\
    return val;\
}\
void T::set(size_t a, size_t b, double val) {\
    if((a > string) || (a < 1) || (b > pillars) || (b < 1)){\
        cout << "Error method get" << endl;\
        exit(1);\
    }\
    (*(matrix[a - 1]))[b] = val;\
}\
size_t T::num_rows() const {return string;}\
size_t T::num_collums() const {return pillars;}\
T::~T(){\
    if(copy_m != nullptr){\
        copy_m->~T();\
        copy_m = nullptr;\
    }\
    for(size_t i = 0; i < string; i++) {\
        if (matrix[i] != nullptr) matrix[i]->~StringMatrix();\
        delete matrix[i];\
    }\
    delete [] matrix;\
}\
bool T::operator ==(T const &M) const{\
    bool fl = true;\
    if((string != M.string) || (pillars != M.pillars))\
        return false;\
    for(size_t i = 0; i < string; i++) {\
        if (*(matrix[i]) != *(M.matrix[i])) {\
            fl = false;\
            break;\
        }\
    }\
    return fl;\
}\
bool T::operator !=(T const &M) const{\
    return !(*this == M);\
}\
T& T::operator= (T const &M) {\
    for(size_t i = 0; i < string; i++){\
        matrix[i]->~StringMatrix();\
    }\
    if(this != &M) delete [] matrix;\
    matrix = new StringMatrix*[M.string];\
    pillars = M.pillars;\
    string = M.string;\
    copy_m = nullptr;\
    for(size_t i = 0; i < M.string; i++)\
        matrix[i] = new StringMatrix;\
    for(size_t i = 0; i < string; i++){\
        *(matrix[i]) = *(M.matrix[i]);\
    }\
    return *this;\
}\
T& T::operator+ (T const &M){\
    if(copy_m != nullptr){\
        copy_m->~T();\
        copy_m = nullptr;\
    }\
    if((M.string != string) || (M.pillars != pillars)){\
        cout << "Error operator +" << endl;\
        exit(1);\
    }\
    T *Val_M;\
    Val_M = new T(*this);\
    copy_m = Val_M;\
    for(size_t i = 0; i<string; i++)\
        *(Val_M->matrix[i]) = *(Val_M->matrix[i]) + *(M.matrix[i]);\
    return *Val_M;\
}\
StringMatrix* T::operator+ (size_t k){\
    if((k > string) || (k < 1)){\
        cout << "Error operator +" << endl;\
        exit(1);\
    }\
    return matrix[k-1];\
}\
const StringMatrix* T::operator + (size_t k) const{\
    if((k > string) || (k < 1)){\
        cout << "Error operator +" << endl;\
        exit(1);\
    }\
    return matrix[k-1];\
}\
T& T::operator* (T const &M){\
    if(copy_m != nullptr){\
        copy_m->~T();\
        copy_m = nullptr;\
    }\
    if(M.string != pillars){\
        cout << "Error operator *" << endl;\
        exit(1);\
    }\
    T *Val_M;\
    Val_M = new T(string, M.pillars);\
    copy_m = Val_M;\
    for (size_t i = 1; i < string + 1; i++)\
        for (size_t j = 1; j < M.pillars + 1; j++) {\
            double Sum = 0;\
            for (size_t k = 1; k < pillars + 1; k++)\
                Sum += (this->get(i, k) * M.get(k, j));\
            if((Sum - 0.0) >= E) (*(Val_M->matrix[i-1]))[j] = Sum;\
        }\
    return *Val_M;\
}
Realization_Matrix(SparseMatrix)
Realization_Matrix(DenseMatrix)
SparseMatrix::SparseMatrix(size_t a, size_t b): string(a), pillars(b){
    copy_m = nullptr;
    matrix = new StringMatrix*[a];
    for(size_t i = 0; i < a; i++)
        matrix[i] = new StringMatrix;
}
DenseMatrix::DenseMatrix(size_t a, size_t b): string(a), pillars(b){
    copy_m = nullptr;
    matrix = new StringMatrix*[a];
    for(size_t i = 0; i < a; i++)
        matrix[i] = new StringMatrix;
    for(size_t i = 1; i < string + 1; i++)
        for(size_t j = 1; j < pillars + 1; j++)
            this->set(i, j, 0);
}

Iterator::Iterator(bool fl, IterableSparseMatrix* S, IterableDenseMatrix* D):flag(fl),
                                                 ISM(S), IDM(D), n_string(0), list(nullptr){}
Iterator::Iterator(List* p, bool fl, IterableSparseMatrix * S, IterableDenseMatrix* D):flag(fl),
                                                 ISM(S), IDM(D), n_string(0),  list(p){}
Iterator::Iterator(const Iterator& it): flag(it.flag), ISM(it.ISM), IDM(it.IDM),
					n_string(it.n_string),  list(it.list){}
size_t& Iterator::row() {
    return n_string;
}
size_t& Iterator::column() {
    return list->n_pillars;
}
Iterator& Iterator::operator++(){
    if(flag){
        List *p;
        size_t i = n_string;
        size_t k = list->n_pillars;
        size_t j;
        if(ISM != nullptr) j = ISM->Matrix()->num_rows();
        else j = IDM->Matrix()->num_rows();
        while(true) {
            i++;
            if(i > j){
                p = nullptr;
                break;
            }
            if(ISM != nullptr) p = (*ISM->Matrix())[i].elem_row();
            else p = (*IDM->Matrix())[i].elem_row();
            while ((p != nullptr) && (p->n_pillars < k))
                p = p->next;
            if(p == nullptr) continue;
            if(p->n_pillars == k) break;
            if(p->n_pillars > k) continue;
        }
        n_string = i;
        list = p;
    }
    else list = list->next;
    return *this;
}
Iterator& Iterator::operator--(){
    if(flag){
        List *p;
        size_t i = n_string;
        size_t k = list->n_pillars;
        while(true) {
            i--;
            if(i < 1){
                p = nullptr;
                break;
            }
            if(ISM != nullptr) p = (*ISM->Matrix())[i].elem_row();
            else p = (*IDM->Matrix())[i].elem_row();
            while ((p != nullptr) && (p->n_pillars < k))
                p = p->next;
            if(p == nullptr) continue;
            if(p->n_pillars == k) break;
            if(p->n_pillars > k) continue;
        }
        n_string = i;
        list = p;
    }
    else list = list->prev;
    return *this;
}
bool Iterator::Iterator::operator ==(Iterator const& it) const{
    return ((list == it.list) && (flag == it.flag));
}
bool Iterator::operator !=(Iterator const& it) const{
    return !(*this == it);
}
double Iterator::operator *() const{
    return list->a;
}
IterableSparseMatrix::IterableSparseMatrix(size_t a): matrix(new SparseMatrix(a, a)){}
IterableSparseMatrix::IterableSparseMatrix(IterableSparseMatrix& ISM): matrix(new SparseMatrix(*ISM.matrix)){}
size_t IterableSparseMatrix::size() const {return matrix->num_rows();}
Iterator IterableSparseMatrix::iterate_rows(size_t k) const{
    Iterator it((*matrix)[k].elem_row(), false, const_cast<IterableSparseMatrix *>(this), nullptr);
    return it;
}
SparseMatrix* IterableSparseMatrix::Matrix() const{
    return matrix;
}
Iterator IterableSparseMatrix::iterate_columns(size_t k) const{
    List *p;
    size_t i = 0;
    while(true) {
        i++;
        if(i > matrix->num_rows()){
            p = nullptr;
            break;
        }
        p = (*matrix)[i].elem_row();
        while ((p != nullptr) && (p->n_pillars + 1 < k))
            p = p->next;
        if(p == nullptr) continue;
        if(p->n_pillars + 1 == k) break;
        if(p->n_pillars + 1 > k) continue;
    }
    Iterator it(p, true, const_cast<IterableSparseMatrix *>(this), nullptr);
    it.row() = i;
    return it;
}
Iterator IterableSparseMatrix::end_rows(size_t k) const{
    Iterator it(nullptr, false, const_cast<IterableSparseMatrix *>(this), nullptr);
    return it;
}
Iterator IterableSparseMatrix::end_columns(size_t k) const{
    Iterator it(nullptr, true, const_cast<IterableSparseMatrix *>(this), nullptr);
    return it;
}
void IterableSparseMatrix::set(size_t a, size_t b, double value) const{
    matrix->set(a, b, value);
}
IterableSparseMatrix::~IterableSparseMatrix(){
    delete matrix;
}
IterableDenseMatrix::IterableDenseMatrix(size_t a): matrix(new DenseMatrix(a, a)){}
IterableDenseMatrix::IterableDenseMatrix(IterableDenseMatrix& ISM): matrix(new DenseMatrix(*ISM.matrix)){}
size_t IterableDenseMatrix::size() const {return matrix->num_rows();}
Iterator IterableDenseMatrix::iterate_rows(size_t k) const{
    Iterator it((*matrix)[k].elem_row(), false, nullptr, const_cast<IterableDenseMatrix *>(this));
    return it;
}
Iterator IterableDenseMatrix::iterate_columns(size_t k) const{
    List *p;
    size_t i = 0;
    while(true) {
        i++;
        if(i > matrix->num_rows()){
            p = nullptr;
            break;
        }
        p = (*matrix)[i].elem_row();
        while ((p != nullptr) && (p->n_pillars + 1 < k))
            p = p->next;
        if(p == nullptr) continue;
        if(p->n_pillars + 1 == k) break;
        if(p->n_pillars + 1 > k) continue;
    }
    Iterator it(p, true, nullptr, const_cast<IterableDenseMatrix *>(this));
    it.row() = i;
    return it;
}
DenseMatrix* IterableDenseMatrix::Matrix() const{
    return matrix;
}
Iterator IterableDenseMatrix::end_rows(size_t k) const{
    Iterator it(nullptr, false, nullptr, const_cast<IterableDenseMatrix *>(this));
    return it;
}
Iterator IterableDenseMatrix::end_columns(size_t k) const{
    Iterator it(nullptr, true, nullptr, const_cast<IterableDenseMatrix *>(this));
    return it;
}
void IterableDenseMatrix::set(size_t a, size_t b, double value) const{
    matrix->set(a, b, value);
}
IterableDenseMatrix::~IterableDenseMatrix(){
    delete matrix;
}
std::set<size_t> BFS(IterableSquareMatrix const& M, size_t k){
    queue <size_t> dop_set;
    std::set <size_t> value = {};
    dop_set.push(k);
    while(!dop_set.empty()){
        size_t ver = dop_set.front();
        dop_set.pop();
        value.insert(ver);
        Iterator it_b = M.iterate_rows(ver);
        Iterator it_e = M.end_rows(ver);
        for(Iterator it = it_b; it != it_e; ++it){
            if(((*it) - 0 > E) && (value.find(it.column() + 1) == value.end())){
                dop_set.push(it.column() + 1);
            }
        }
    }
    return value;
}
size_t connect_comp(IterableSquareMatrix const &M){
    size_t val = 0;
    set <size_t> st = {};
    set <size_t> d_st = {};
    for(size_t i = 1; i < M.size() + 1; i++){
        if(st.find(i) == st.end()) {
            d_st = BFS(M, i);
            for (auto it : d_st){
                st.insert(it);
            }
            d_st.clear();
            ++val;
        }
    }
    return val;
}
size_t short_way(IterableSquareMatrix const &M, size_t ver1, size_t ver2, set <size_t>& val){
    if(ver1 == ver2) return 0;
    size_t value, min_value = M.size() + 5;
    set <size_t> st;
    Iterator it_b = M.iterate_columns(ver1);
    Iterator it_e = M.end_columns(ver1);
    for(Iterator it = it_b; it != it_e; ++it)
        if((*it) - 0 > E) st.insert(it.row());
    val.insert(ver1);
    if(st.find(ver2) == st.end()){
        for(auto it1 : st){
            if(val.find(it1) == val.end())
                value = short_way(M, it1, ver2, val);
            else continue;
            if(value != 0) value += 1;
            else continue;
            if(value < min_value) min_value = value;
        }
    }
    else {
        val.insert(ver2);
        min_value = 1;
    }
    if(min_value == M.size() + 5) return 0;
    return min_value;
}
size_t diameter(IterableSquareMatrix const &M){
    size_t max = 0;
    for(size_t i = 1; i < M.size() + 1; i++)
        for(size_t j = i + 1; j < M.size() + 1; j++){
            set <size_t> val;
            size_t k = short_way(M, i, j, val);
            if(max < k) max = k;
        }
    return max;
}