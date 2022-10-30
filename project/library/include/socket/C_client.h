#ifndef HOTELPROJECT_C_CLIENT_H
#define HOTELPROJECT_C_CLIENT_H
#include <arpa/inet.h>
#include <string>
#define DISCONNECT "!DISCONNECT"
#define GET_CLIENTS "!CLIENTS"
#define GET_ROOMS "!ROOMS"
#define GET_RESERVATIONS "!RESERVATIONS"
#define PASSWORD "!PASSWD"



class C_client {
    int sockfd,conn_success;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    //unsigned int value;
public:
    C_client();
    ~C_client();
    bool createConnection();
    std::string sendMessage(std::string msg);

};


#endif //HOTELPROJECT_C_CLIENT_H
