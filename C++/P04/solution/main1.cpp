#include <iostream>
#include "sock_wrap.hpp"

int main(){
    char s[] = "file_socket";
    UnClientSocket sok = UnClientSocket(s);
    sleep(2);
    sok.Connect();
    std::string str2 = sok.GetString();
    std::cout << str2 << std::endl;
    char str1[1024];
    std::cin >> str1;
    sok.PutString(str1);
    str2 = sok.GetString();
    std::cout << str2 << std::endl;
    std::cin >> str2;
    sok.PutString(str2);
    str2 = sok.GetString();
    std::cout << str2 << std::endl;
    std::cin >> str2;
    sok.PutString(str2);
    return 0;
}
