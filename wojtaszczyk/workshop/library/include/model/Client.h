#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include <iostream>
#include <vector>
#include "typedef.h"
#include <algorithm>
#include <boost/date_time.hpp>
#include "ClientType.h"
#include "exceptions/ClientException.h"
#include <regex>


class Rent;
class Address;
class Rent;

class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    AddressPtr  ClientAddress;
    ClientTypePtr clientType;
    bool archive=0;

    Client();
public:
    std::string getClientInfo() const;
    Client(const std::string &Initial_FirstName, const std::string &Initial_LastName,
           const std::string &Initial_PersonalID, AddressPtr Initial_adres,const ClientTypePtr &Initial_Type);
    ~Client();
    const std::string &getClientFirstName() const;
    const std::string &getClientLastName() const;
    const std::string &getClientPersonalID() const;
    AddressPtr getClientAddress() const;
    void setClientFirstName(const std::string &Changed_FirstName);
    void setClientLastName(const std::string &Changed_LastName);
    void setClientAddress(AddressPtr ChangedAddress );
    void setClientType(const ClientTypePtr &clientType);
    unsigned int getMaxVehicles() const;
    double applyDiscount(double price) const;
    void setArchive(bool archive);
    bool isArchive() const;
    std::string getInfo() const;
    const std::string &getId() const;
};
class FirstNamePredicate {
private:
    std::regex pattern;
public:
    FirstNamePredicate( const std::string &pattern1) : pattern(pattern1) {}
    bool operator()(const ClientPtr &ptr) const{
        return std::regex_match(ptr->getClientFirstName(),pattern);
    }
};
class LastNamePredicate {
private:
    std::regex pattern;
public:
    LastNamePredicate(const std::string &pattern1) : pattern(pattern1) {}
    bool operator()(const ClientPtr &ptr) const{
        return std::regex_match(ptr->getClientLastName(),pattern);
    }
};



#endif //CARRENTAL_CLIENT_H
