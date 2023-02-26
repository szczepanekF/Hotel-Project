#include "socket/C_client.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sstream>
#include "managers/ClientManager.h"

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



string C_client::sendMessage(const string &msg){
    stringstream strs;
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

int C_client::login(const string &pid,const string &passwd) {
    if (conn_success<0) {
        return -2;
    }
    string help = sendMessage(GET_PASSWORD);
    string possiblePasswd = sendMessage(pid);

    if (possiblePasswd == NO_CLIENT) {
        std::cout<<"1";
        return -1;
    } else if (possiblePasswd != passwd) {
        return 0;
    }
    loggedPID=pid;
    return 1;
}

int C_client::saveInfo(const string &msg) {
    if (conn_success<0) {
        return -2;
    }
    sendMessage(SAVE_INFO);
    string abc = sendMessage(msg);

    if(abc == "SAVED")
        return 1;
    return 0;
}

void C_client::setLoggedPid(const std::string &pid) {
    C_client::loggedPID = pid;
}

std::string C_client::getLoggedPid() {
    return loggedPID;
}

void C_client::updateType(const std::string &i) {
    updateClient(i,"Client_type");
}

void C_client::updateBalance(const std::string &i) {
    updateClient(i,"bill");
}

void C_client::updateClient(const string &new_value, const string &what) {
    if (conn_success<0) {
        return;
    }
    string updatemsg = sendMessage(UPDATE_CLIENT);
    sendMessage(loggedPID+"#"+new_value+"#"+what);
}

void C_client::deleteReservation(const string &i) {
    if (conn_success<0) {
        return;
    }
    string deletemsg = sendMessage(DELETE_RES);
    sendMessage(i);
}

void C_client::updateResType(const string &new_value) {
    if (conn_success<0) {
        return;
    }
    string deletemsg = sendMessage(UPDATE_RES);
    sendMessage(new_value);
}


