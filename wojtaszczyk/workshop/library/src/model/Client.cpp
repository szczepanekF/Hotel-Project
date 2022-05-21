#include "model/Client.h"
#include "model/Address.h"
#include "model/Rent.h"


using namespace std;

    Client:: Client()
    {

    }
    Client:: ~Client()
    {

    }
    string Client::getClientInfo() const
    {
        return "Client "+FirstName+" "+LastName+" "+PersonalID+" "+ ClientAddress->getAddressInfo()+" "+clientType->getTypeInfo();
    }
    Client::Client(const std::string &Initial_FirstName, const std::string &Initial_LastName,
                   const std::string &Initial_PersonalID, AddressPtr Initial_adres,const ClientTypePtr &Initial_Type)
        try:FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),ClientAddress(Initial_adres),clientType(Initial_Type)
        {
            if(Initial_adres== nullptr){
                throw ClientException("null Address Error");
            }
            if(Initial_Type==nullptr){
                throw ClientException("null Type Error");
            }
            if(Initial_FirstName.empty()){
                throw ClientException("empty First Name");
            }
            if(Initial_LastName.empty()){
                throw ClientException("empty Last Name");
            }
            if(Initial_PersonalID.empty()){
                throw ClientException("empty PersonalID");
            }

        }catch(const ClientException &e){
            cout<<e.what()<<'\n';
        }



    const std::string &Client::getClientFirstName() const
    {
        return FirstName;
    }
    const std::string &Client::getClientLastName() const
    {
        return LastName;
    }

    const std::string &Client::getClientPersonalID() const
    {
        return PersonalID;
    }
    void Client::setClientFirstName(const std::string &Changed_FirstName)
    {
        if(Changed_FirstName!="")
        FirstName=Changed_FirstName;
        else
            throw ClientException("null Argument Error");
    }
    void Client::setClientLastName(const std::string &Changed_LastName)
    {
        if(Changed_LastName!="")
        LastName=Changed_LastName;
        else
            throw ClientException("null Argument Error");
    }
     AddressPtr Client::getClientAddress() const {
        return ClientAddress;
    }
    void Client::setClientAddress(AddressPtr ChangedAddress) {
        if (ChangedAddress!=nullptr)
            ClientAddress=ChangedAddress;
        else
            throw ClientException("null Argument Error");
    }

void Client::setClientType(const ClientTypePtr &clientType) {
    if(clientType== nullptr){
        throw ClientException("null Argument Error");
    }else
            Client::clientType = clientType;
}

unsigned int Client::getMaxVehicles() const {
    return clientType->getMaxVehilces();
}

double Client::applyDiscount(double price) const {
    return clientType->applyDiscount(price);
}

bool Client::isArchive() const {
    return archive;
}

void Client::setArchive(bool archive) {
    Client::archive = archive;
}

std::string Client::getInfo() const {
    return getClientInfo();
}

const std::string &Client::getId() const {
    return getClientPersonalID();
}

