#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include <iostream>
#include <vector>
#include "typedef.h"
#include <algorithm>
#include <boost/date_time.hpp>
#include "ClientType.h"


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
};




#endif //CARRENTAL_CLIENT_H
