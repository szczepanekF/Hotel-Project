#include "repositories/ClientRepository.h"
//#include <iostream>
//#include <string>
#include <algorithm>
using namespace std;

ClientRepository::~ClientRepository()
{
    for(unsigned int i = 0;i<clientList.size();i++)
    {
        ClientPtr cl=clientList[i];
//        delete cl;
    }
}

ClientPtr ClientRepository::get_client(unsigned int i) const
{
    if(i < size_clientList())
        return clientList[i];
    return nullptr;
}

void ClientRepository::add_client(const ClientPtr new_Client)
{
    if(new_Client != nullptr)
        clientList.push_back(new_Client);
}

void ClientRepository::remove_client(ClientPtr rm_Client)
{
    if(rm_Client != nullptr)
    {
        clientList.erase(remove(clientList.begin(),clientList.end(),rm_Client),clientList.end());
//        delete rm_Client;
    }
}

const std::string ClientRepository::report_clientList() const
{
    stringstream ss;

//    for(int i = 0; i<size();i++)
//        for(int j = 0; j<clientList[i]->get_rentNumber();j++){
//            report += i;
//            report += clientList[i]->get_currentRent(j)->getRentInfo();
//            report += '\n';
//        }
    for(int i = 0; i<size_clientList();i++)
    {
        ss << clientList[i]->getClientInfo() << "\n";
    }
    string s = ss.str();
    return s;
}

const unsigned int ClientRepository::size_clientList() const
{
    return clientList.size();
}

vector<ClientPtr> ClientRepository::findBy(ClientPredicate predicate) const {
    vector<ClientPtr> found;
    for (unsigned int i = 0; i < size_clientList(); i++) {
        ClientPtr client = get_client(i);
        if (client != nullptr && predicate(client)) {
            found.push_back(client);
        }
    }
    return found;
}
bool testtrue1(const ClientPtr ptr)
{
    return true;
}
std::vector <ClientPtr> ClientRepository::findAll() const
{
   return findBy(testtrue1);
}






ClientPtr ClientRepository::findByPersonalId(const std::string &personalID) const
{
    ClientPredicate clientpid = [personalID](ClientPtr ptr)
    {
        return ptr->getpersonalID()==personalID;
    };
    vector<ClientPtr> found = findBy(clientpid);

    if(found.size()==0)
        return nullptr;
    return found[0];
}

