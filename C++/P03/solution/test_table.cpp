#include "dbms.hpp"

int main(){
    unsigned count = 3;
    FieldDef* fd = new FieldDef[count];
    fd[0].type = Text;
    fd[0].len = 20;
    strcpy(fd[0].name, "Name");
    fd[1].type = Text;
    fd[1].len = 20;
    strcpy(fd[1].name, "Surname");
    fd[2].type = Long;
    fd[2].len = 10;
    strcpy(fd[2].name, "Age");
    My_Table T;
    T.Fill_Struct(count, fd);
    char name[4] = {'v', 'a', 'y', '\0'};
    T.Create_Table(name);
    T.Open();
    std::vector<std::pair<enum FieldType, std::pair<long, char*>>> mas;
    std::pair<enum FieldType, std::pair<long, char*>> par;
    par.first = Text;
    char m1[7] = {'K', 'i', 'r', 'i', 'l', 'l', '\0'};
    par.second.second = m1;
    mas.push_back(par);
    par.first = Text;
    char m2[6] = {'G', 'o', 'r', 'e', 'v', '\0'};
    par.second.second = m2;
    mas.push_back(par);
    par.first = Long;
    par.second.first = 19;
    mas.push_back(par);
    T.Add(mas);
    par.first = Text;
    char m3[6] = {'G', 'o', 's', 'h', 'a', '\0'};
    par.second.second = m3;
    mas.push_back(par);
    par.first = Text;
    char m4[6] = {'D', 'e', 'm', 'o', 'n', '\0'};
    par.second.second = m4;
    mas.push_back(par);
    par.first = Long;
    par.second.first = 19;
    mas.push_back(par);
    T.Add(mas);
    T.ReadFirst();
    char m5[5] = {'N', 'a', 'm', 'e', '\0'};
    std::cout << T.FieldNum(m5) << std::endl;
    std::cout << T.FieldLen(m5) << std::endl;
    std::cout << T.FieldType(m5) << std::endl;
    std::cout << T.FieldName(1) << std::endl;
    std::cout << T.GetText(m5) << std::endl;
    T.ReadNext();
    char m6[4] = {'A', 'g', 'e', '\0'};
    std::cout << T.FieldNum(m6) << std::endl;
    std::cout << T.FieldLen(m6) << std::endl;
    std::cout << T.FieldType(m6) << std::endl;
    std::cout << T.FieldName(2) << std::endl;
    std::cout << T.GetLong(m6) << std::endl;
    delete[] fd;
}
