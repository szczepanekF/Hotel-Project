//
// Created by student on 17.03.2022.
//

#include "model/Client.h"
#include <iostream>


using namespace std;

    Client:: Client()
    {

    }
    Client:: ~Client()
    {

    }
    string Client::GetClientInfo()
    {
        return "Client "+FirstName+" "+LastName+" "+PersonalID;
    }
    Client::Client(std::string Initial_FirstName, std::string Initial_LastName, std::string Initial_PersonalID)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID)
        {

        }

    std::string Client::GetClientFirstName()
    {
        return FirstName;
    }
    std::string Client::GetClientLastName()
    {
        return LastName;
    }

    std::string Client::GetClientPersonalID()
    {
        return PersonalID;
    }
    void Client::SetClientFirstName(std::string Changed_FirstName)
    {
        if(Changed_FirstName!=" ")
        FirstName=Changed_FirstName;
    }
    void Client::SetClientLastName(std::string Changed_LastName)
    {
        if(Changed_LastName!=" ")
        LastName=Changed_LastName;
    }