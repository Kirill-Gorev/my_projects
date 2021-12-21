#include <iostream>
#include "sock_wrap.hpp"

const char * address = "mysocket";

int main(int argc, char* argv[]){
    try{
        UnClientSocket sock(address);
        sock.Connect();
        sock.PutString("Hello from client!");
        std::cout << "Read from server: " << sock.GetString() << std::endl;
    }
    catch(Exception &e){
        e.Report();
    }
    return 0;
}
