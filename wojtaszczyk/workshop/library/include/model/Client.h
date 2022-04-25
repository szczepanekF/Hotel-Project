
#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include <iostream>
#include <vector>
#include "typedef.h"
#include <algorithm>
#include <boost/date_time.hpp>


class Rent;
class Address;
class Rent;

class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    AddressPtr  ClientAddress;
    std::vector <RentPtr> currentRents;
    Client();
public:
    std::string getClientInfo() const;
    Client(const std::string &Initial_FirstName, const std::string &Initial_LastName, const std::string &Initial_PersonalID,AddressPtr Initial_adres);
    ~Client();
    const std::string &getClientFirstName() const;
    const std::string &getClientLastName() const;
    const std::string &getClientPersonalID() const;
    AddressPtr getClientAddress() const;
    void setClientFirstName(const std::string &Changed_FirstName);
    void setClientLastName(const std::string &Changed_LastName);
    void setClientAddress(AddressPtr ChangedAddress );
    void addNewRent(RentPtr NewRent);
    unsigned int getClient_RentNumber() const;
    RentPtr getClientRent(const unsigned int &i) const;
    std::string getFullClientInfo() const;
    void removeClientRent(RentPtr rent);
};




#endif //CARRENTAL_CLIENT_H
