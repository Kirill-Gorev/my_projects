#include <iostream>
#include "sock_wrap.hpp"

int main(){
    char s[] = "file_socket";
    UnServerSocket sok = UnServerSocket(s);
    BaseSocket* sok_new = sok.Accept();
    char str1[] = "Hello, my name is server, what is your name?";
    sok_new->PutString(str1);
    std::string str2 = sok_new->GetString();
    std::cout << str2 << std::endl;
    str2 = "Good, how old are you?";
    sok_new->PutString(str2);
    str2 = sok_new->GetString();
    std::cout << str2 << std::endl;
    str2 = "Good, finish";
    sok_new->PutString(str2);
    str2 = sok_new->GetString();
    std::cout << str2 << std::endl;
    return 0;
}
