#ifndef HOTELPROJECT_CLIENTMANAGER_H
#define HOTELPROJECT_CLIENTMANAGER_H

#include "model/typedefs.h"
#include <vector>

class ClientRepository;

class ClientManager {
private:
    ClientRepositoryPtr clients;
public:
    explicit ClientManager(const ClientRepositoryPtr &initial_clients);
    ClientManager();
    virtual ~ClientManager();
    ClientPtr regiterClient(const std::string &firstName,const std::string &lastName,const std::string &personalID,const ClientTypePtr &clientType);
    void unregisterClient(const std::string &personalID) const;
    ClientPtr getClient(const std::string &personalID) const;
    std::vector<ClientPtr> findClients(ClientPredicate predicate) const;
    std::vector<ClientPtr> findAllClients() const;
    void changeClientTypetoStandard(const std::string &personalID) const;
    void changeClientTypetoLongTerm(const std::string &personalID) const;

};


#endif //HOTELPROJECT_CLIENTMANAGER_H
