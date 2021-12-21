#include "Analiz.hpp"
#include <string>

int main(){
    std::string s = "SELECT * FROM Students WHERE First_name LIKE '[ABC][^mno]_x%'";
    Scanner Sc(s);
    Sc.parser();
    Sc.print();
    Sc.SA();
    return 0;
}