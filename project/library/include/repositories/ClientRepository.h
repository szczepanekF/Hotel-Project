//
// Created by student on 30.05.2022.
//

#ifndef HOTELPROJECT_CLIENTREPOSITORY_H
#define HOTELPROJECT_CLIENTREPOSITORY_H
#include "repositories/Repository.h"

class Client;
class ClientError;

class ClientRepository : public Repository<Client,ClientError>{
public:
    ClientRepository();
    ~ClientRepository() override;
};


#endif //HOTELPROJECT_CLIENTREPOSITORY_H
