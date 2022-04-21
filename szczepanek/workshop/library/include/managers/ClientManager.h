//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_CLIENTMANAGER_H
#define CARRENTAL_CLIENTMANAGER_H
#include "../typedefs.h"
#include "../repositories/ClientRepository.h"


class ClientManager{
    ClientRepository clientRepository;
public:

    ClientPtr getClient(const std::string &PID) const;
    ClientPtr registerClient(const std::string &Initial_FirstName,const std::string &Initial_LastName,const std::string &Initial_PersonalID,AddressPtr init_address,
                              ClientTypePtr init_clientType);
    void unregisterClient(ClientPtr clientptr);
    std::vector<ClientPtr> findClients(ClientPredicate predicate) const;
};

#endif //CARRENTAL_CLIENTMANAGER_H
