#include "model/Client.h"
#include "model/ClientType.h"
#include "exceptions/ClientError.h"



Client::Client(const std::string &initial_firtsName, const std::string &initial_lastName, const std::string &initial_personalId,
               const ClientTypePtr &initial_clientType) try: firstName(initial_firtsName), lastName(initial_lastName), personalID(initial_personalId),
                                                             ClientType(initial_clientType), archive(false),bill(0) {

    if(initial_firtsName.empty()){
        throw ClientError("ERROR Empty first name");
    }
    if(initial_lastName.empty()){
        throw ClientError("ERROR Empty last name");
    }
    if(initial_personalId.empty()){
        throw ClientError("ERROR Empty personalId");
    }
    if(initial_clientType== nullptr){
        throw ClientError("ERROR Null client type");
    }
//    if(initial_clientType->getClientTypeInfo() == "Long Term Client"){
//        bill=300;
//    }else if(initial_clientType->getClientTypeInfo() == "Standard Client"){
//        bill=100;
//    }else{
//        bill=0;
//    }
    }catch(const ClientError &e){
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

double Client::getBill() const {
    return bill;
}

void Client::setFirstName(const std::string &initial_firtsName) {
    if(initial_firtsName.empty()){
        throw ClientError("ERROR Empty first name");
    }
    Client::firstName = initial_firtsName;
}

void Client::setLastName(const std::string &initial_lastName) {
    if(initial_lastName.empty()){
        throw ClientError("ERROR Empty last name");
    }
    Client::lastName = initial_lastName;
}

void Client::setClientType(const ClientTypePtr &initial_clientType) {
    if(initial_clientType== nullptr){
        throw ClientError("ERROR Null client type");
    }
    //if(initial_clientType->getMaxDays() > getClientType()->getMaxDays()){
        ClientType=initial_clientType;
//        double s=getBill();
//        if(initial_clientType->getMaxDays() == 30){
//            s+=300;
//        }else if(initial_clientType->getMaxDays() == 7){
//            s+=100;
//        }
//        setBill(s);
//    }

}

void Client::setArchive(bool initial_archive) {
    Client::archive = initial_archive;
}

void Client::setBill(double initial_bill) {
    Client::bill = initial_bill;
}

unsigned int Client::getMaxDays() const {
    return getClientType()->getMaxDays();
}

bool Client::acceptDiscount() const {
    return getClientType()->applyDiscount();
}

std::string Client::getInfo() const {
    return getClientType()->getClientTypeInfo() + " " + getFirstName() + " " + getLastName() + " " + getId() + " bill equal: " + std::to_string(getBill());
}
