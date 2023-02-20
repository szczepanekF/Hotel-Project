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
#define SAVE_INFO "!SAVE"
#define UPDATE_CLIENT "!UPDATE_CLIENT"

#include "typedefs.h"

class C_client {
    int sockfd,conn_success;
    std::string loggedPID;


private:
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
public:
    C_client();
    ~C_client();
    bool createConnection();
    int login(const std::string &pid,const std::string &passwd);
    void updateClient(const std::string &value,const std::string &what);
    void updateType(const std::string &i);
    void updateBill(const std::string &i);
    std::string sendMessage(const std::string &msg);
    int saveInfo(const std::string &msg);
    int getConnSuccess() const;
    std::string getLoggedPid();
    void setLoggedPid(const std::string &loggedClient);


};


#endif //HOTELPROJECT_C_CLIENT_H
