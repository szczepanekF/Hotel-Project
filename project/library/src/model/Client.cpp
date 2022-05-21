#include "model/Client.h"
#include "model/ClientType.h"



Client::Client(const std::string &firtsName, const std::string &lastName, const std::string &personalId,
               const ClientTypePtr &clientType) : firstName(firtsName), lastName(lastName), personalID(personalId),
                                                  ClientType(clientType), archive(false) {
    if(clientType->getMaxDays()==30){
        bill=300;
    }else if(clientType->getMaxDays()==7){
        bill=100;
    }else{
        bill=0;
    }


}

Client::~Client() {

}

const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getLastName() const {
    return lastName;
}

const std::string &Client::getPersonalId() const {
    return personalID;
}

const ClientTypePtr &Client::getClientType() const {
    return ClientType;
}

bool Client::isArchive() const {
    return archive;
}

double Client::getBill() const {
    return bill;
}

void Client::setFirstName(const std::string &firtsName) {
    Client::firstName = firtsName;
}

void Client::setLastName(const std::string &lastName) {
    Client::lastName = lastName;
}

void Client::setClientType(const ClientTypePtr &clientType) {
        if(clientType->getMaxDays()>getClientType()->getMaxDays()){
            ClientType=clientType;
            double s=getBill();
            if(clientType->getMaxDays()==30){
                s+=300;
            }else if(clientType->getMaxDays()==7){
                s+=100;
            }
            setBill(s);
        }

}

void Client::setArchive(bool archive) {
    Client::archive = archive;
}

void Client::setBill(double bill) {
    Client::bill = bill;
}

int Client::getMaxDays() const {
    return getClientType()->getMaxDays();
}

bool Client::acceptDiscount() const {
    return getClientType()->applyDiscount();
}

std::string Client::getInfo() const {
    return getClientType()->getClientTypeInfo() + " " + getFirstName() + " " + getLastName() + " " + getPersonalId() + " o rachunku rownym: " + std::to_string(getBill());
}
