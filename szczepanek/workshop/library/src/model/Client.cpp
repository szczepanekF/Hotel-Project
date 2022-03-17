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
    Client::Client(string Initial_FirstName, string Initial_LastName, string Initial_PersonalID)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID)
        {

        }

    string Client::GetClientFirstName()
    {
        return FirstName;
    }
    string Client::GetClientLastName()
    {
        return LastName;
    }

    string Client::GetClientPersonalID()
    {
        return PersonalID;
    }
    void Client::SetClientFirstName(string Changed_FirstName)
    {
        if(Changed_FirstName!="")
        FirstName=Changed_FirstName;
    }
    void Client::SetClientLastName(string Changed_LastName)
    {
        if(Changed_LastName!="")
        LastName=Changed_LastName;
    }