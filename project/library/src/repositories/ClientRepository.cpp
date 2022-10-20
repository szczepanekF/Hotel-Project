//
// Created by student on 30.05.2022.
//

#include "repositories/ClientRepository.h"
#include "model/Client.h"
#include "exceptions/ClientError.h"
#include <iostream>
ClientRepository::~ClientRepository()=default;
ClientRepository::ClientRepository()=default;

std::vector<std::vector<std::string>> ClientRepository::readInfo(c_client* conn) {
    std::string clients = conn->sendMessage(GET_CLIENTS);
    std::string delimiterEnter = "\n";
    std::string delimiterComma = ",";
    size_t pos1 = 0;
    std::string token;
    std::vector<std::string> splittedClients;
    std::vector<std::vector<std::string>> infoAboutClients;

    while ((pos1 = clients.find(delimiterEnter)) != std::string::npos) {

        token = clients.substr(0, pos1);
        splittedClients.push_back(token);
        clients.erase(0, pos1 + delimiterEnter.length());
    }

    pos1 = 0;

    int size = splittedClients.size();

    for(int i=0;i<size;i++) {
        infoAboutClients.push_back( std::vector<std::string>() );
        while ((pos1 = splittedClients[i].find(delimiterComma)) != std::string::npos) {

            token = splittedClients[i].substr(0, pos1);
            infoAboutClients[i].push_back(token);
            splittedClients[i].erase(0, pos1 + delimiterComma.length());
        }
        infoAboutClients[i].push_back(splittedClients[i]);
    }

    return infoAboutClients;
}

