#include "model/Client.h"
#include "model/ClientType.h"
#include "exceptions/ClientError.h"



Client::Client(const std::string &initial_firstName, const std::string &initial_lastName, const std::string &initial_personalId,
               const ClientTypePtr &initial_clientType) :firstName(initial_firstName), lastName(initial_lastName), personalID(initial_personalId),
                                                             ClientType(initial_clientType), archive(false), balance(0) {

        if(initial_firstName.empty()){
            throw ClientError("ERROR Empty first name");
        }
        if(initial_lastName.empty()){
            throw ClientError("ERROR Empty last name");
        }
        if(initial_personalId.empty()){
            throw ClientError("ERROR Empty personalId");
        }
        if(initial_clientType== nullptr){
            throw ClientError("ERROR Null C_client type");
        }
    }



Client::~Client() = default;

const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getLastName() const {
    return lastName;
}

const std::string &Client::getId() const {
    return personalID;
}

const ClientTypePtr &Client::getClientType() const {
    return ClientType;
}

bool Client::isArchive() const {
    return archive;
}

double Client::getBalance() const {
    return balance;
}

void Client::setFirstName(const std::string &new_firstName) {
    if(new_firstName.empty()){
        throw ClientError("ERROR Empty first name");
    }
    Client::firstName = new_firstName;
}

void Client::setLastName(const std::string &new_lastName) {
    if(new_lastName.empty()){
        throw ClientError("ERROR Empty last name");
    }
    Client::lastName = new_lastName;
}

void Client::setClientType(const ClientTypePtr &new_clientType) {
    if(new_clientType == nullptr){
        throw ClientError("ERROR Null C_client type");
    }
        ClientType=new_clientType;
}

void Client::setArchive(bool new_archive) {
    Client::archive = new_archive;
}

void Client::setBalance(double new_bill) {
    Client::balance = new_bill;
}

unsigned int Client::getMaxDays() const {
    return getClientType()->getMaxDays();
}

bool Client::acceptDiscount() const {
    return getClientType()->applyDiscount();
}

std::string Client::getInfo() const {
    std::string ArchiveInfo;
    if(isArchive()){
        ArchiveInfo="is archive";
    }else{
        ArchiveInfo="is not archive";
    }
    return getClientType()->getClientTypeInfo() + " " + getFirstName() + " " + getLastName() + " " + getId() + " balance equal: " + std::to_string(
            getBalance()) + " " + ArchiveInfo ;
}

std::string Client::toDBInfo() const {
    std::string clientTypeInt;
    if (getClientType()->getClientTypeInfo() == "Base account") {
        clientTypeInt = "0";
    } else if (getClientType()->getClientTypeInfo() == "Gold account") {
        clientTypeInt = "1";
    } else if (getClientType()->getClientTypeInfo() == "Diamond account") {
        clientTypeInt = "2";
    }


    return getFirstName()+"#"+getLastName()+"#"+getId()+"#"+clientTypeInt;
}
