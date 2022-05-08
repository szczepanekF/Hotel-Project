#ifndef CARRENTAL_CLIENTMANAGER_H
#define CARRENTAL_CLIENTMANAGER_H
#include "repositories/StorageContainer.h"
#include <functional>

class ClientManager {
private:
    ClientRepositoryPtr currentClients;
public:
    ClientPtr getClient(const std::string &ID) const;
    ClientPtr registerClient(const std::string &Initial_FirstName, const std::string &Initial_LastName,
                             const std::string &Initial_PersonalID, AddressPtr Initial_adres, ClientTypePtr Initial_Type);
    void unregisterClient(const std::string &ID);
    std::vector<ClientPtr> findClients(ClientPredicate predicate) const;
    std::vector<ClientPtr> findAllClients() const;
    ClientManager();

};


#endif //CARRENTAL_CLIENTMANAGER_H
