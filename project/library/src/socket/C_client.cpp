#include "socket/C_client.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sstream>


#define PORT "5050"
#define IP "192.168.0.55"
using namespace std;

C_client::C_client() {
    conn_success = -1;
}

C_client::~C_client() {
    sendMessage(DISCONNECT);
    close(conn_success);
}

bool C_client::createConnection() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening C_client");
        exit(1);
    } else if (sockfd > 0) {
        cout << "SOCKET OPENED" << endl;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, IP, &(serv_addr.sin_addr.s_addr));



    cout << "attempting to connect to server" << endl;

    conn_success = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (conn_success < 0) {
        perror("ERROR connecting");
        return 0;
    } else {
        cout << "connection successful" << endl;
        return 1;
    }

}



std::string C_client::sendMessage(std::string msg){
    std:stringstream strs;
    strs << msg.size();
    string length = strs.str();
    send(sockfd,length.c_str(),length.size(),0);
    recv(sockfd,buffer,1024,0);
    memset(buffer,0,sizeof buffer);
    send(sockfd, msg.c_str(), msg.size(), 0);
    recv(sockfd,buffer,1024,0);
    return buffer;
}

int C_client::getConnSuccess() const {
    return conn_success;
}

int C_client::login(std::string pid, std::string passwd) {
    if (conn_success<0) {
        return -2;
    }
    std::string help = sendMessage(GET_PASSWORD);
    std::string possiblePasswd = sendMessage(pid);

    if (possiblePasswd == NO_CLIENT) {
        return -1;
    } else if (possiblePasswd != passwd) {
        return 0;
    }
    logged_pid = pid;
    return 1;
}

void C_client::setLoggedPid(const string &loggedPid) {
    logged_pid = loggedPid;
}

int C_client::saveInfo(std::string msg) {
    if (conn_success<0) {
        return -2;
    }
    sendMessage(SAVE_INFO);
    std::string abc = sendMessage(msg);

    if(abc == "SAVED")
        return 1;
    return 0;
}
