#include "model/Client.h"
#include <iostream>



using namespace std;

    Client:: Client()
    {

    }
    Client:: ~Client()
    {
        //ddress;
    }

    Client::Client(const string &Initial_FirstName,const string &Initial_LastName,const string &Initial_PersonalID, AddressPtr init_address,
                   ClientTypePtr init_clientType)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),address(init_address),
         clientType(init_clientType)
        {
//            currentRents.clear();
        }
    string Client::getClientInfo() const
    {
        return "Client "+clientType->getTypeInfo()+FirstName+" "+LastName+" "+PersonalID + " " + address->getAddressInfo();
    }
//    string Client::getFullClientInfo() const
//    {
//        stringstream ss;
//        ss <<getClientInfo();
//
//
//        int x = get_rentNumber();
//        if(x>0)
//        ss<<"\nRents: \n";
//        for(int i=0;i<x;i++)
//            ss<<get_currentRent(i)->get_vehicle()->getVehicleInfo()<<'\n';
//        string s = ss.str();
//        return s;
//    }
    const string &Client::getfirstName() const
    {
        return FirstName;
    }
    const string &Client::getlastName() const
    {
        return LastName;
    }

    const string &Client::getpersonalID() const
    {
        return PersonalID;
    }

    const AddressPtr Client::get_address() const
    {
        return address;
    }

//    const unsigned int Client::get_rentNumber() const
//    {
//        return currentRents.size();
//    }
//    const RentPtr Client::get_currentRent(const unsigned int &i) const
//    {
//        if (i < currentRents.size()){
//            return currentRents[i];
//        }
//        return NULL;
//    }
//
//    void Client::remove_currentRent(RentPtr rent)
//    {
//        currentRents.erase(remove(currentRents.begin(),currentRents.end(),rent),currentRents.end());
//    }


    void Client::setfirstName(string const &Changed_FirstName)
    {
            if(Changed_FirstName!=""){
                FirstName=Changed_FirstName;
            }
    }
    void Client::setlastName(string const &Changed_LastName)
    {
            if(Changed_LastName!="")
            LastName=Changed_LastName;
    }

    void Client::set_address(AddressPtr new_address)
    {
            if(new_address!=NULL) address=new_address;
    }
//    void Client::AddRent(RentPtr new_rent)
//    {
//            currentRents.push_back(new_rent);
//    }

    void Client::set_clientType(ClientTypePtr new_clientType)
    {
        clientType=new_clientType;
    }

    const double Client::applyDiscount(const double &price) const {
        return clientType->applyDiscount(price);
    }

    const unsigned int Client::getMaxVehicles() const {
        return clientType->getMaxVehicles();
    }

bool Client::isArchive() const {
    return archive;
}

void Client::setArchive(bool archive) {
    Client::archive = archive;
}
