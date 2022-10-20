//
// Created by student on 30.05.2022.
//

#ifndef HOTELPROJECT_CLIENTREPOSITORY_H
#define HOTELPROJECT_CLIENTREPOSITORY_H
#include "repositories/Repository.h"
#include "socket/c_client.h"

class Client;
class ClientError;

class ClientRepository : public Repository<Client,ClientError>{
public:
    ClientRepository();
    ~ClientRepository() override;
    std::vector<std::vector<std::string>> readInfo(c_client* conn);
};


#endif //HOTELPROJECT_CLIENTREPOSITORY_H
