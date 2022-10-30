#ifndef HOTELPROJECT_CLIENTREPOSITORY_H
#define HOTELPROJECT_CLIENTREPOSITORY_H
#include "repositories/Repository.h"
#include "socket/C_client.h"

class Client;
class ClientError;

class ClientRepository : public Repository<Client,ClientError>{
public:
    ClientRepository();
    ~ClientRepository() override;

};


#endif //HOTELPROJECT_CLIENTREPOSITORY_H
