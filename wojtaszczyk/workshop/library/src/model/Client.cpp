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
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),ClientAddress(Initial_adres),clientType(Initial_Type)
        {

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
        if(Changed_FirstName!=" ")
        FirstName=Changed_FirstName;
    }
    void Client::setClientLastName(const std::string &Changed_LastName)
    {
        if(Changed_LastName!=" ")
        LastName=Changed_LastName;
    }
     AddressPtr Client::getClientAddress() const {
        return ClientAddress;
    }
    void Client::setClientAddress(AddressPtr ChangedAddress) {
        if (ChangedAddress!=nullptr)
            ClientAddress=ChangedAddress;
    }

void Client::setClientType(const ClientTypePtr &clientType) {
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

