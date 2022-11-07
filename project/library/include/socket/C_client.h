#ifndef HOTELPROJECT_C_CLIENT_H
#define HOTELPROJECT_C_CLIENT_H
#include <arpa/inet.h>
#include <string>
#define DISCONNECT "!DISCONNECT"
#define GET_CLIENTS "!CLIENTS"
#define GET_ROOMS "!ROOMS"
#define GET_RESERVATIONS "!RESERVATIONS"
#define GET_PASSWORD "!PASSWD"
#define NO_CLIENT "!NO_CLIENT"


class C_client {
    int sockfd,conn_success;
    std::string logged_pid;
public:
    void setLoggedPid(const std::string &loggedPid);

public:
    int getConnSuccess() const;

private:
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    //unsigned int value;
public:
    C_client();
    ~C_client();
    bool createConnection();
    int login(std::string pid,std::string passwd);
    std::string sendMessage(std::string msg);


};


#endif //HOTELPROJECT_C_CLIENT_H
