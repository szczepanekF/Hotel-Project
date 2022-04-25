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
        return "Client "+FirstName+" "+LastName+" "+PersonalID+" "+ ClientAddress->getAddressInfo();
    }
    Client::Client(const std::string &Initial_FirstName, const std::string &Initial_LastName,const std::string &Initial_PersonalID, AddressPtr Initial_address)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),ClientAddress(Initial_address)
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
    void Client::addNewRent(RentPtr NewRent) {
        currentRents.push_back(NewRent);
    }

unsigned int Client::getClient_RentNumber() const{
    return currentRents.size();
}

RentPtr Client::getClientRent(const unsigned int &i) const{
    return currentRents[i];
}

string Client::getFullClientInfo() const {
    std::stringstream ss;

    unsigned int i= this->getClient_RentNumber();
    ss << this->getClientInfo() << endl;
    for (unsigned int x=0;x<i;x++)
    {
       ss << this->getClientRent(x)->getRentInfo() << endl;
    }
    return ss.str();
}
void Client::removeClientRent(RentPtr rent) {

    currentRents.erase(remove(currentRents.begin(),currentRents.end(),rent),currentRents.end());

}