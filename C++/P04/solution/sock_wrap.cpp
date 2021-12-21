#include "sock_wrap.hpp"

void Exception::Report (){
    std::cerr << "Error code: " << m_ErrCode << std::endl;
    std::cerr << GetMessage() << std::endl;
}

std::string SocketException::GetMessage (){
    switch(m_ErrCode){
        case 0:
            return "Error: ESE_SUCCESS";
        case 1:
            return "Error: ESE_SOCKCREATE";
        case 2:
            return "Error: ESE_SOCKCONN";
        case 3:
            return  "Error: ESE_SOCKILLEGAL";
        case 4:
            return  "Error: ESE_SOCKHOSTNAME";
        case 5:
            return  "Error: ESE_SOCKSEND";
        case 6:
            return "Error: ESE_SOCKRECV";
        case 7:
            return "Error: ESE_SOCKBIND";
        case 8:
            return "Error: ESE_SOCKLISTEN";
        case 9:
            return "Error: ESE_SOCKACCEPT";
        default:
            return "Unreal";
    }
}

struct sockaddr_un* SocketAddress::operator* (){
    return m_pAddr;
}

UnSocketAddress::UnSocketAddress (const char * SockName){
    struct sockaddr_un *addr = new struct sockaddr_un;
    strcpy(addr->sun_path, SockName);
    addr->sun_family = AF_UNIX;
    m_pAddr = addr;
}

UnSocketAddress::~UnSocketAddress(){
    delete m_pAddr;
}

int UnSocketAddress::GetLength(){
    return sizeof(*m_pAddr);
}

UnSocketAddress* UnSocketAddress::Clone(){
    UnSocketAddress* sock = new UnSocketAddress(m_pAddr->sun_path);
    (**sock)->sun_family = AF_UNIX;
    return sock;
}

void BaseSocket::Write(void * buf, int len){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    if(send(m_Socket, buf, len, 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
}

void BaseSocket::PutChar(char c){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    int l = 1;
    if(send(m_Socket, &l, sizeof(int), 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
    if(send(m_Socket, &c, 1, 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
}

void BaseSocket::PutString(const char * str){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    const char* c = str;
    int l = 0;
    while(*c != '\0'){
        c++;
        l++;
    }
    if(send(m_Socket, &l, sizeof(int), 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
    if(send(m_Socket, str, l, 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
}

void BaseSocket::PutString(const std::string& s){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    int l = s.length();
    if(send(m_Socket, &l, sizeof(int), 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
    if(send(m_Socket, s.c_str(), l, 0) == -1){
        SocketException e(ESE_SOCKSEND);
        throw e;
    }
}

BaseSocket::~BaseSocket(){
    shutdown(m_Socket, SHUT_RDWR);
    close(m_Socket);
    delete m_pAddr;
}

int BaseSocket::Read (void * buf, int len){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    if(recv(m_Socket, buf, len, 0) == -1){
        SocketException e(ESE_SOCKRECV);
        throw e;
    }
    return 0;
}

char BaseSocket::GetChar(){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    char c;
    int l;
    Read(&l, sizeof(int));
    if(recv(m_Socket, &c, 1, 0) == -1){
        SocketException e(ESE_SOCKRECV);
        throw e;
    }
    return c;
}

std::string BaseSocket::GetString(){
    if(!CheckSocket()){
        SocketException e(ESE_SOCKILLEGAL);
        throw e;
    }
    int l;
    Read(&l, sizeof(int));
    char s[l];
    if(recv(m_Socket, s, l, 0) == -1){
        SocketException e(ESE_SOCKRECV);
        throw e;
    }
    std::string str;
    for(int i = 0; i < l; i++)
        str.push_back(s[i]);
    return str;
}

int BaseSocket::GetSockDescriptor(){
    return m_Socket;
}

bool BaseSocket::CheckSocket(){
    if((m_Socket == -1) || (m_pAddr == NULL))
        return false;
    else return true;
}

void ClientSocket::Connect(){
    if(connect(m_Socket, (struct sockaddr*)(**m_pAddr), 
                     sizeof(struct sockaddr_un)) == -1){
        SocketException e(ESE_SOCKCONN);
        throw e;
    }
}

BaseSocket* ServerSocket::Accept(){
    Bind();
    Listen(1);
    int a = accept(m_Socket, NULL, NULL);
    if(a == -1){
        SocketException e(ESE_SOCKACCEPT);
        throw e;
    }
    UnSocketAddress* m1_pAddr = new UnSocketAddress((**m_pAddr)->sun_path);
    BaseSocket* s_new = new BaseSocket(a, m1_pAddr);
    return s_new;
}

void ServerSocket::Bind(){
    if(bind(m_Socket, (struct sockaddr*)(**m_pAddr), 
                  sizeof(struct sockaddr_un)) == -1){
        SocketException e(ESE_SOCKBIND);
        throw e;
    }
}

void ServerSocket::Listen(int BackLog){
    if(listen(m_Socket,BackLog) == -1){
        SocketException e(ESE_SOCKLISTEN);
        throw e;
    }
}

UnClientSocket::UnClientSocket(const char * Address){
    m_pAddr = new UnSocketAddress(Address);
    m_Socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(m_Socket == -1){
        SocketException e(ESE_SOCKCREATE);
        throw e;
    }
}

UnServerSocket::UnServerSocket(const char * Address){
    m_pAddr = new UnSocketAddress(Address);
    m_Socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(m_Socket == -1){
        SocketException e(ESE_SOCKCREATE);
        throw e;
    }
}
