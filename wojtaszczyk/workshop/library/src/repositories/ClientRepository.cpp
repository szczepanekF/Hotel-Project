
#include "repositories/ClientRepository.h"

ClientPtr ClientRepository::get(const unsigned int &i) const {
    if (i<=this->size() && i>=0){
    return ClientRepo[i];}
    else
        return nullptr;
}

void ClientRepository::add(ClientPtr client) {
    if(client!= nullptr){
    ClientRepo.push_back(client);
    }
}

void ClientRepository::remove(ClientPtr client) {
    ClientRepo.erase(std::remove(ClientRepo.begin(),ClientRepo.end(),client),ClientRepo.end());
    delete client;
}

std::string ClientRepository::report() const {
    std::stringstream ss;
    unsigned int x=this->size();
    for (int i=0;i<x;i++)
    {
        ss << this->get(i)->getClientInfo() << '\n';
    }
    return ss.str();
}

unsigned int ClientRepository::size() const {
    return ClientRepo.size();
}

ClientRepository::~ClientRepository() {
    for(int i=0;i<size();i++)
    {
        ClientPtr d=get(i);
        delete d;
    }

}

std::vector <ClientPtr> ClientRepository::findBy(ClientPredicate predicate) const {
    std::vector<ClientPtr> found;
    for (unsigned int i = 0; i < size(); i++) {
        ClientPtr client = get(i);
        if (client != nullptr && predicate(client)) {
            found.push_back(client);
        }
    }
    return found;
}

std::vector<ClientPtr> ClientRepository::findAll() const {
   return findBy(allClientpredicate);
}

bool allClientpredicate(const ClientPtr ptr) {
    return true;
}

bool clientID1(const ClientPtr ptr) {
    return ptr->getClientPersonalID()=="1";
}
