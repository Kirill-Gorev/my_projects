#include <iostream>
#include <set>
#include <queue>

struct List{
    List(double value, size_t n);
    double a;
    size_t n_pillars;
    List *next, *prev;
};
double const E = 0.000000001;
double const Znach = 0;
class StringMatrix{
    void delete_List();
    List *string;
public:
    StringMatrix();
    double& operator [] (size_t k);
    double operator [] (size_t k) const;
    double* operator + (size_t k);
    const double* operator + (size_t k) const;
    StringMatrix(StringMatrix const &str);
    double get(size_t b) const;
    List* elem_row() const;
    bool operator != (StringMatrix const &str) const;
    bool operator == (StringMatrix const &str) const;
    StringMatrix& operator = (StringMatrix const &str);
    StringMatrix& operator + (StringMatrix const &str) const;
    ~StringMatrix();
};
#define Class_Matrix(T) \
    class T{\
        size_t string;\
        size_t pillars;\
        StringMatrix **matrix;\
        T *copy_m;\
    public:\
        T(size_t a, size_t b);\
        T(T &M);\
        StringMatrix &operator [] (size_t k);\
        const StringMatrix &operator [] (size_t k) const;\
        double get(size_t a, size_t b) const;\
        void set(size_t a, size_t b, double val);\
        size_t num_rows() const;\
        size_t num_collums() const;\
        ~T();\
        bool operator == (T const &M) const;\
        bool operator != (T const &M) const;\
        T& operator = (T const &M);\
        T& operator + (T const &M);\
        StringMatrix* operator + (size_t k);\
        const StringMatrix* operator + (size_t k) const;\
        T& operator * (T const &M);\
    };
Class_Matrix(SparseMatrix)
Class_Matrix(DenseMatrix)
class Iterator;
class IterableSquareMatrix{
public:
    virtual Iterator iterate_rows(size_t) const = 0;
    virtual Iterator iterate_columns(size_t) const = 0;
    virtual Iterator end_rows(size_t) const = 0;
    virtual Iterator end_columns(size_t) const = 0;
    virtual size_t size() const = 0;
    virtual void set(size_t a, size_t b, double value) const = 0;
    virtual ~IterableSquareMatrix() = default;
};
class IterableSparseMatrix: public IterableSquareMatrix{
    SparseMatrix* matrix;
public:
    SparseMatrix* Matrix() const;
    explicit IterableSparseMatrix(size_t a);
    IterableSparseMatrix(IterableSparseMatrix& ISM);
    size_t size() const override;
    Iterator iterate_rows(size_t k) const override;
    Iterator iterate_columns(size_t k) const override;
    Iterator end_rows(size_t k) const override;
    Iterator end_columns(size_t k) const override;
    void set(size_t a, size_t b, double value) const override;
    ~IterableSparseMatrix() override;
};
class IterableDenseMatrix: public IterableSquareMatrix{
    DenseMatrix* matrix;
public:
    DenseMatrix* Matrix() const;
    explicit IterableDenseMatrix(size_t a);
    IterableDenseMatrix(IterableDenseMatrix& ISM);
    size_t size() const override;
    Iterator iterate_rows(size_t k) const override;
    Iterator iterate_columns(size_t k) const override;
    Iterator end_rows(size_t k) const override;
    Iterator end_columns(size_t k) const override;
    void set(size_t a, size_t b, double value) const override;
    ~IterableDenseMatrix() override;
};
class Iterator:public std::iterator<std::input_iterator_tag, List>{
    bool flag;
    IterableSparseMatrix *ISM;
    IterableDenseMatrix *IDM;
    size_t n_string;
    List* list;
public:
    Iterator() = delete;
    Iterator(bool fl, IterableSparseMatrix* S, IterableDenseMatrix* D);
    Iterator(List* p, bool fl, IterableSparseMatrix* S, IterableDenseMatrix* D);
    Iterator(const Iterator& it);
    Iterator& operator++();
    Iterator& operator--();
    size_t& row();
    size_t& column();
    bool operator ==(Iterator const& it) const;
    bool operator !=(Iterator const& it) const;
    double operator *() const;
};
std::set<size_t> BFS(IterableSquareMatrix const & M, size_t k);
size_t connect_comp(IterableSquareMatrix const &M);
size_t short_way(IterableSquareMatrix const & M, size_t ver1, size_t ver2, std::set <size_t>& val);
size_t diameter(IterableSquareMatrix const & M);