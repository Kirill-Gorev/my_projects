#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
    IterableDenseMatrix M(15);
    for(size_t i = 1; i < M.size() - 2; i++)
        for(size_t j = 1; j < M.size() - 2; j++)
            M.set(i, j, random() % 2);
    M.set(13, 15, 1);
    M.set(15, 13, 1);
    cout << "DenseMatrix:" << endl;
    for(size_t i = 1; i < M.size() + 1; i++){
        cout << "row " << i << ": ";
        for(auto it = M.iterate_rows(i); it != M.end_rows(i); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << "component_connect: " << connect_comp(M) << endl;
    set <size_t> val;
    for(size_t i = 1; i < M.size() + 1; i++)
        for(size_t j = 1; j < M.size() + 1; j++){
            val.clear();
            cout << "short_way " << i << "-" << j << ' ' << short_way(M, i, j, val) << endl;
    	}
    cout << "diametr: " << diameter(M) << endl;
    IterableSparseMatrix M1(15);
    for(size_t i = 1; i < M1.size() - 1; i++)
        for(size_t j = 1; j < M1.size() - 1; j++){
            size_t l = random() % 2;
            if(l) M1.set(i, j, l);
        }
    M1.set(14, 15, 1);
    M1.set(15, 14, 1);
    cout << "SparseMatrix:" << endl;
    for(size_t i = 1; i < M1.size() + 1; i++){
        cout << "column " << i << ": ";
        for(auto it = M1.iterate_columns(i); it != M1.end_columns(i); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << "component_connect: " << connect_comp(M1) << endl;
    set <size_t> val1;
    for(size_t i = 1; i < M1.size() + 1; i++)
        for(size_t j = 1; j < M1.size() + 1; j++){
            val1.clear();
            cout << "short_way " << i << "-" << j << ' ' << short_way(M1, i, j, val1) << endl;
    	}
    cout << "diametr: " << diameter(M1) << endl;
    return 0;
}
