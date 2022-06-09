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

    ClientPtr regiterClient(const std::string &initial_firstName, const std::string &initial_lastName, const std::string &initial_personalID, const ClientTypePtr &initial_clientType);
    void unregisterClient(const std::string &personalID) const;
    ClientPtr getClient(const std::string &personalID) const;
    std::vector<ClientPtr> findClients(const ClientPredicate &predicate) const;
    std::vector<ClientPtr> findAllClients() const;
    void changeClientTypetoStandard(const std::string &personalID) const;
    void changeClientTypetoLongTerm(const std::string &personalID) const;

};


#endif //HOTELPROJECT_CLIENTMANAGER_H
