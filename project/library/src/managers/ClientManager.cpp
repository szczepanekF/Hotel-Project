//
// Created by student on 05.06.2022.
//

#include "managers/ClientManager.h"


#include "model/Client.h"
#include "model/Standard.h"
#include "model/longTerm.h"
#include "model/ClientType.h"
#include "repositories/ClientRepository.h"


ClientManager::ClientManager(const ClientRepositoryPtr &initial_clients) : clients(initial_clients) {}

ClientManager::~ClientManager() = default;

ClientManager::ClientManager() = default;

ClientPtr ClientManager::regiterClient(const std::string &initial_firstName, const std::string &initial_lastName, const std::string &initial_personalID,
                                       const ClientTypePtr &initial_clientType) {
    try{
        getClient(initial_personalID);
    }catch(const ClientError &e){
        ClientPtr client= std::make_shared<Client>(initial_firstName, initial_lastName, initial_personalID, initial_clientType);
        if(initial_clientType->getClientTypeInfo() == "Long Term Client"){
            client->setBill(300);
        }else if(initial_clientType->getClientTypeInfo() == "Standard Client"){
            client->setBill(100);
        }
        clients->add(client);
        return client;
    }
    throw ClientError("ERROR already exists: "+getClient(initial_personalID)->getInfo());

}

void ClientManager::unregisterClient(const std::string &personalID) const {
    getClient(personalID)->setArchive(true);
}

 ClientPtr ClientManager::getClient(const std::string &personalID) const{
    return clients->findById(personalID);
}

std::vector<ClientPtr> ClientManager::findClients(const ClientPredicate &predicate) const {
    return clients->findBy(predicate);
}

std::vector<ClientPtr> ClientManager::findAllClients() const {
    ClientPredicate f =[](const ClientPtr& ptr)->bool{return !ptr->isArchive();};
    return findClients(f);
}

void ClientManager::changeClientTypetoStandard(const std::string &personalID) const {
    ClientTypePtr type= std::make_shared<Standard>();
    ClientPtr client= getClient(personalID);
    if(client->getMaxDays()<type->getMaxDays()){
        client->setClientType(type);
        double s=client->getBill();
        s+=100;
        client->setBill(s);
    }else if(client->getMaxDays()==type->getMaxDays()){
        throw ClientError("ERROR cant change to equal type");
    }else{
        throw ClientError("ERROR cant change to lower type");
    }

}

void ClientManager::changeClientTypetoLongTerm(const std::string &personalID) const {
    ClientTypePtr type= std::make_shared<longTerm>();
    ClientPtr client= getClient(personalID);
    if(client->getMaxDays()<type->getMaxDays()){
        client->setClientType(type);
        double s=client->getBill();
        s+=300;
        client->setBill(s);
    }else if(client->getMaxDays()==type->getMaxDays()){
        throw ClientError("ERROR cant change to equal type");
    }else{
        throw ClientError("ERROR cant change to lower type");
    }

}
