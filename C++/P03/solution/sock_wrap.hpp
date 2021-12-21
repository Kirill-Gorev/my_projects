#include <cstring>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>


class Exception{
protected:
    int m_ErrCode;
public:
    Exception (int errcode ) : m_ErrCode(errcode) {}
    void Report();
    virtual std::string GetMessage() = 0;
};

enum SocketExceptionCode{
	ESE_SUCCESS,
	ESE_SOCKCREATE,
	ESE_SOCKCONN,
	ESE_SOCKILLEGAL,
	ESE_SOCKHOSTNAME,
	ESE_SOCKSEND,
	ESE_SOCKRECV,
	ESE_SOCKBIND,
	ESE_SOCKLISTEN,
	ESE_SOCKACCEPT
};

class SocketException: public Exception{
public:
    SocketException(SocketExceptionCode errcode):Exception(errcode) {}
    std::string GetMessage();
};

class SocketAddress {
protected:
    struct sockaddr_un * m_pAddr;
public:
    SocketAddress () : m_pAddr(NULL) {}
    virtual ~SocketAddress () {}
    virtual int GetLength() = 0;
    virtual SocketAddress * Clone() = 0;
    struct sockaddr_un* operator* ();
};

class UnSocketAddress : public SocketAddress {
public:
    UnSocketAddress (const char * SockName);
    ~UnSocketAddress ();
    int GetLength ();
    UnSocketAddress * Clone();
};

class BaseSocket {
public:
    explicit BaseSocket (int sd = -1, SocketAddress * pAddr = NULL):
                       m_Socket(sd), m_pAddr(pAddr) {}
    virtual ~BaseSocket();
    void Write(void * buf, int len);
    void PutChar(char c);
    void PutString(const char * str);
    void PutString(const std::string& s);
    int Read (void * buf, int len);
    char GetChar();
    std::string GetString();
    int GetSockDescriptor();
protected:
    int m_Socket;
    SocketAddress * m_pAddr;
    bool CheckSocket();
};

class ClientSocket: public BaseSocket {
public:
    void Connect();
    ~ClientSocket() {};
};

class ServerSocket: public BaseSocket{
public:
    BaseSocket *Accept();
protected:
    void Bind();
    void Listen(int BackLog);
    ~ServerSocket() {};
};

class UnClientSocket: public ClientSocket {
public:
    UnClientSocket(const char * Address);
    ~UnClientSocket() {};
};

class UnServerSocket: public ServerSocket {
public:
    UnServerSocket(const char * Address);
    ~UnServerSocket() {};
};
