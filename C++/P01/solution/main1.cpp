#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
cout << "Hello, World!" << endl;
SparseMatrix m1(10,20);
SparseMatrix m2(10,20);
m1[1][1] = 10.6;
m1[10][11] = 13;
m1[1][7] = 17;
m1[2][3] = 5.1;
*(*(m1 + 1) + 1) = 1.9;
m1.set(1, 3, 99.1);
*(*(m1 + 5) + 7) = 20;
SparseMatrix m4 = m1;
cout << "fl: " << (m4 == m1) << " (1)" << endl;
m2[1][3] = 10;
m2[1][1] = 13.7;
m2[1][8] = 5;
m2[2][3] = 5;
*(*(m2 + 2) + 3) = 1;
m2.set(5, 7, 9.7);
*(*(m2 + 5) + 7) = 20.5;
SparseMatrix m3 = m1 + m2;
cout << "m3[1][1]: " << m3.get(1, 1) << " (15.6)" << endl;
cout << "m3[2][3]: " << m3[2][3] << " (6.1)" << endl;
cout << "m3[1][8]: " << *(*(m3 + 1) + 8) << " (5)" << endl;
return 0;
}
