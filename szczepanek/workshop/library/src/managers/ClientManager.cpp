#include "managers/ClientManager.h"

using namespace std;

ClientPtr ClientManager::getClient(const std::string &PID) const {
    return clientRepository.findByPersonalId(PID);
}

ClientPtr ClientManager::registerClient(const std::string &Initial_FirstName, const std::string &Initial_LastName,
                                         const std::string &Initial_PersonalID, AddressPtr init_address,
                                         ClientTypePtr init_clientType)
 {
    ClientPtr newclient;
    newclient = getClient(Initial_PersonalID);
    if(newclient != nullptr)
        return newclient;
    newclient = std::make_shared<Client>(Initial_FirstName,Initial_LastName,Initial_PersonalID,init_address,init_clientType);
    clientRepository.add_client(newclient);
    return newclient;
}

void ClientManager::unregisterClient(ClientPtr clientptr)
{
    if(getClient(clientptr->getpersonalID()) == clientptr)
        clientptr->setArchive(true);
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) const
{

    ClientPredicate archive= [predicate](ClientPtr ptr)
    {
        return predicate(ptr) && ptr->isArchive()==false;
    };
    vector<ClientPtr> found;
    for (unsigned int i = 0; i < clientRepository.size_clientList(); i++) {
        ClientPtr client = clientRepository.get_client(i);
        if (client != nullptr && archive(client)) {
            found.push_back(client);
        }
    }
    return found;
}