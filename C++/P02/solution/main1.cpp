#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
    const IterableDenseMatrix M(15);
    for(size_t i = 1; i < M.size() + 1; i++)
        for(size_t j = 1; j < M.size() + 1; j++)
            if(i % 2 == j % 2)
                M.set(i, j, 1);
            else M.set(i, j, 0);
    cout << "DenseMatrix:" << endl;
    for(size_t i = 1; i < M.size() + 1; i++){
        cout << "column " << i << ": ";
        for(auto it = M.iterate_columns(i); it != M.end_columns(i); ++it)
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
    const IterableSparseMatrix M1(15);
    for(size_t i = 1; i < M1.size() - 1; i++)
        for(size_t j = 1; j < M1.size() - 1; j++){
            if(i % 2 == j % 2)
                M1.set(i, j, 1);
        }
    M1.set(14, 15, 1);
    M1.set(15, 14, 1);
    cout << "SparseMatrix:" << endl;
    for(size_t i = 1; i < M1.size() + 1; i++){
        cout << "row " << i << ": ";
        for(auto it = M1.iterate_rows(i); it != M1.end_rows(i); ++it)
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