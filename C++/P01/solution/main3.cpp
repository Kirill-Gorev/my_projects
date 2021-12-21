#include <iostream>
#include "matrix.hpp"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    SparseMatrix m1(3,4);
    SparseMatrix m2(4,3);
    m1[1][1] = 3.7;
    m1[1][2] = 17.1;
    m1[1][3] = 5;
    m1[1][4] = 10;
    *(*(m1 + 2) + 1) = 1.9;
    *(*(m1 + 2) + 2) = 1.7;
    m1[2][3] = 1.3;
    m1[2][4] = 1.1;
    m2.set(1, 1, 3.7);
    m2[1][2] = 17.1;
    m2[1][3] = 5;
    m2.set(2, 1, 10);
    m2[2][2] = 1.9;
    m2[2][3] = 1.7;
    m2[3][3] = 1.3;
    m2[4][2] = 1.1;
    *(*(m2 + 4) + 2) = 3.3;
    cout << m2[4][2] << " (3.3)" << endl;
    const SparseMatrix m3 = m1;
    cout << "m3 == m1: " << (m3 == m1) << " (1)" << endl;
    cout << m3[2][3] << " (1.3) " << m3[3][1] << " (0) " << endl;
    cout << *(*(m3 + 2) + 3) << " (1.3) " << *(*(m3 + 3) + 1) << " (0) " << endl;
    cout << m3.get(2, 3) << " (1.3) " << m3.get(3, 1) << " (0) " << endl;
    return 0;
}
