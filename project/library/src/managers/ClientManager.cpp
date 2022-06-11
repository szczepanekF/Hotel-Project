//
// Created by student on 05.06.2022.
//

#include "managers/ClientManager.h"

#include <utility>
#include "model/Client.h"
#include "model/Standard.h"
#include "model/longTerm.h"
#include "model/ClientType.h"
#include "repositories/ClientRepository.h"
#include <fstream>

ClientManager::ClientManager(const ClientRepositoryPtr &initial_clients) : clients(initial_clients) {}

ClientManager::~ClientManager(){
    std::ofstream plik("../../application_status/Clients.txt");
    plik<<"CLIENTS: \n";
    for(int i=0;i<clients->size();i++)
    {
        plik<<clients->get(i)->getInfo()<<'\n';
    }
    plik.close();
};

ClientManager::ClientManager() = default;

ClientPtr ClientManager::regiterClient(const std::string &firstName, const std::string &lastName, const std::string &personalID,
                             const ClientTypePtr &clientType) {
    try{
        getClient(personalID);
    }catch(const ClientError &e){
        ClientPtr client= std::make_shared<Client>(firstName,lastName,personalID,clientType);
        if(clientType->getClientTypeInfo() == "Long Term Client"){
            client->setBill(300);
        }else if(clientType->getClientTypeInfo() == "Standard Client"){
            client->setBill(100);
        }
        clients->add(client);
        return client;
    }
    throw ClientError("ERROR already exists: "+getClient(personalID)->getInfo());

}

void ClientManager::unregisterClient(const std::string &personalID) const {
    getClient(personalID)->setArchive(true);
}

 ClientPtr ClientManager::getClient(const std::string &personalID) const{
    return clients->findById(personalID);
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) const {
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
