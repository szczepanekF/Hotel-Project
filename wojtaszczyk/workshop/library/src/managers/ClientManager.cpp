#include "managers/ClientManager.h"

ClientPtr ClientManager::getClient(const std::string &ID) const {
    return currentClients->findByPersonalID(ID);
}

ClientPtr ClientManager::registerClient(const std::string &Initial_FirstName, const std::string &Initial_LastName,
                                        const std::string &Initial_PersonalID, AddressPtr Initial_adres,
                                        ClientTypePtr Initial_Type) {
    if(getClient(Initial_PersonalID)== nullptr)
    {
        ClientPtr client= std::make_shared<Client>(Initial_FirstName,Initial_LastName,Initial_PersonalID,Initial_adres,Initial_Type);
        currentClients->add(client);
        return client;
    }
    else{
        return getClient(Initial_PersonalID);
    }
}

void ClientManager::unregisterClient(const std::string &ID) {
    getClient(ID)->setArchive(true);
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) const {
    ClientPredicate f =[predicate](ClientPtr ptr)->bool{return predicate(ptr) && !ptr->isArchive();};
    return currentClients->findBy(f);
}

std::vector<ClientPtr> ClientManager::findAllClients() const {
    ClientPredicate f =[](ClientPtr ptr)->bool{return true;};
    return findClients(f);
}

ClientManager::ClientManager() {
    currentClients=std::make_shared<ClientRepository>();
}
