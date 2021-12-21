#include <iostream>

struct List{
    List(double value, size_t n);
    double a;
    size_t n_pillars;
    List *next, *prev;
};

double const E = 0.000000001;
double const Znach = 0;

class StringMatrix{
    List *string;
    void delete_List();
public:
    StringMatrix();
    double& operator [] (size_t k);
    double operator [] (size_t k) const;
    double* operator + (size_t k);
    const double* operator + (size_t k) const;
    StringMatrix(StringMatrix const &str);
    double get(size_t b) const;
    bool operator != (StringMatrix const &str) const;
    bool operator == (StringMatrix const &str) const;
    StringMatrix& operator = (StringMatrix const &str);
    StringMatrix& operator + (StringMatrix const &str) const;
    ~StringMatrix();
};

class SparseMatrix{
    size_t string;
    size_t pillars;
    StringMatrix **matrix;
    SparseMatrix *copy_m;
public:
    SparseMatrix(size_t a, size_t b);
    SparseMatrix(SparseMatrix &M);
    StringMatrix &operator [] (size_t k);
    const StringMatrix &operator [] (size_t k) const;
    double get(size_t a, size_t b) const;
    void set(size_t a, size_t b, double val);
    size_t num_rows() const;
    size_t num_collums() const;
    ~SparseMatrix();
    bool operator == (SparseMatrix const &M) const;
    bool operator != (SparseMatrix const &M) const;
    SparseMatrix& operator = (SparseMatrix const &M);
    SparseMatrix& operator + (SparseMatrix const &M);
    StringMatrix* operator + (size_t k);
    const StringMatrix* operator + (size_t k) const;
    SparseMatrix& operator * (SparseMatrix const &M);
};