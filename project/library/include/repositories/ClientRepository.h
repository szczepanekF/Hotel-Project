//
// Created by student on 30.05.2022.
//

#ifndef HOTELPROJECT_CLIENTREPOSITORY_H
#define HOTELPROJECT_CLIENTREPOSITORY_H
#include "repositories/Repository.h"
#include "exceptions/ClientError.h"

class Client;
class ClientRepository : public Repository<Client,ClientError>{
public:
    ClientRepository();
    ~ClientRepository() override;
};


#endif //HOTELPROJECT_CLIENTREPOSITORY_H
