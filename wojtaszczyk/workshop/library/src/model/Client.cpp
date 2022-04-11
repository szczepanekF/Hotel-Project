

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
    string Client::GetClientInfo() const
    {
        return "Client "+FirstName+" "+LastName+" "+PersonalID+" "+ClientAddress->GetAddressInfo();
    }
    Client::Client(const std::string &Initial_FirstName, const std::string &Initial_LastName,const std::string &Initial_PersonalID, Address* Initial_address)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),ClientAddress(Initial_address)
        {

        }

    const std::string &Client::GetClientFirstName() const
    {
        return FirstName;
    }
    const std::string &Client::GetClientLastName() const
    {
        return LastName;
    }

    const std::string &Client::GetClientPersonalID() const
    {
        return PersonalID;
    }
    void Client::SetClientFirstName(const std::string &Changed_FirstName)
    {
        if(Changed_FirstName!=" ")
        FirstName=Changed_FirstName;
    }
    void Client::SetClientLastName(const std::string &Changed_LastName)
    {
        if(Changed_LastName!=" ")
        LastName=Changed_LastName;
    }
     Address* Client::GetClientAddress() const {
        return ClientAddress;
    }
    void Client::SetClientAddress(Address *ChangedAddress) {
        if (ChangedAddress!=nullptr)
            ClientAddress=ChangedAddress;
    }
    void Client::AddNewRent(Rent *NewRent) {
        currentRents.push_back(NewRent);
    }

unsigned int Client::GetClient_RentNumber() const{
    return currentRents.size();
}

Rent *Client::GetClientRent(const unsigned int &i) const{
    return currentRents[i];
}

void Client::GetFullClientInfo() const {
    unsigned int i=this->GetClient_RentNumber();
    cout<<this->GetClientInfo()<<endl;
    for (unsigned int x=0;x<i;x++)
    {
       cout<<this->GetClientRent(x)->GetRentInfo()<<endl;
    }
}
void Client::removeClientRent(Rent *rent) {

    currentRents.erase(remove(currentRents.begin(),currentRents.end(),rent),currentRents.end());
}