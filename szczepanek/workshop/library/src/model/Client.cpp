//
// Created by student on 17.03.2022.
//

#include "model/Client.h"
#include "model/Address.h"
#include <iostream>



using namespace std;

    Client:: Client()
    {

    }
    Client:: ~Client()
    {
        //delete address;
    }

    Client::Client(const string &Initial_FirstName,const string &Initial_LastName,const string &Initial_PersonalID, Address *init_address)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID),address(init_address)
        {
            currentRents.clear();
        }
    string Client::getClientInfo()
    {
        return "Client "+FirstName+" "+LastName+" "+PersonalID + " " + address->getAddressInfo();
    }
    void Client::getFullClientInfo()
    {
        cout<<getClientInfo()<<"|| Rents: \n";
        int x = get_rentNumber();
        for(int i=0;i<x;i++)
            cout<<get_currentRent(i)->get_vehicle()->getVehicleInfo()<<'\n';
    }
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

    const Address *Client::get_address() const
    {
        return address;
    }

    const unsigned int Client::get_rentNumber() const
    {
        return currentRents.size();
    }
    const Rent *Client::get_currentRent(unsigned int i) const
    {
        if (i < currentRents.size()){
            return currentRents[i];
        }
        return NULL;
    }

    void Client::remove_currentRent(Rent *rent)
    {
        currentRents.erase(remove(currentRents.begin(),currentRents.end(),rent));
    }


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

    void Client::set_address(Address *new_address)
    {
            if(new_address!=NULL) address=new_address;
    }
    void Client::AddRent(Rent *new_rent)
    {
            currentRents.push_back(new_rent);
    }
