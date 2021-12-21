#include <iostream>
#include "sock_wrap.hpp"

const char * address = "mysocket";

class MyServerSocket: public UnServerSocket{
public:
    MyServerSocket(): UnServerSocket(address) {}
    void OnAccept(BaseSocket * pConn){
        std::cout << "Read from client: " << pConn->GetString() << std::endl;
        pConn->PutString("Hello from server.");
        delete pConn;
    }
};

int main (){
    try{
    	MyServerSocket sock;
    	for(;;){
    	    BaseSocket* s = sock.Accept();
    	    sock.OnAccept(s);
    	    unlink(address);
    	}
    }
    catch(Exception &e){
        e.Report();
    }
    return 0;
}
