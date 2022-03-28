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
    string Client::getClientInfo()
    {
        return "Client "+FirstName+" "+LastName+" "+PersonalID;
    }
    Client::Client(string Initial_FirstName, string Initial_LastName, string Initial_PersonalID)
        :FirstName(Initial_FirstName),LastName(Initial_LastName),PersonalID(Initial_PersonalID)
        {

        }

    string Client::getfirstName()
    {
        return FirstName;
    }
    string Client::getlastName()
    {
        return LastName;
    }

    string Client::getpersonalID()
    {
        return PersonalID;
    }
    void Client::setfirstName(string Changed_FirstName)
    {
        if(Changed_FirstName!="")
        FirstName=Changed_FirstName;
    }
    void Client::setlastName(string Changed_LastName)
    {
        if(Changed_LastName!="")
        LastName=Changed_LastName;
    }