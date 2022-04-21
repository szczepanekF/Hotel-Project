//
// Created by student on 17.03.2022.
//

#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include "Address.h"
#include "Rent.h"
#include <vector>
#include "typedefs.h"
#include "ClientType.h"

class Rent;
class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    AddressPtr address;
//    std::vector<RentPtr> currentRents;
    ClientTypePtr clientType;
    bool archive=false;

private:

    Client();
public:

    Client(const std::string &Initial_FirstName,const std::string &Initial_LastName,const std::string &Initial_PersonalID,AddressPtr init_address,
           ClientTypePtr init_clientType);
    ~Client();

    std::string getClientInfo() const;
//    std::string getFullClientInfo() const;

    const std::string &getfirstName() const;
    const std::string &getlastName() const;
    const std::string &getpersonalID() const;
    const AddressPtr get_address() const;

//    const unsigned int get_rentNumber() const;
//    const RentPtr get_currentRent(const unsigned int &i) const;

//    void remove_currentRent(RentPtr rent);

    void setfirstName(std::string const &Changed_FirstName);
    void setlastName(std::string const &Changed_LastName);
    void set_address(AddressPtr new_address);

    void set_clientType(ClientTypePtr new_clientType);
    const unsigned int getMaxVehicles() const;
    const double applyDiscount(const double &price) const;


    void setArchive(bool archive);
    bool isArchive() const;
//    void AddRent(RentPtr new_rent);

    };
#endif //CARRENTAL_CLIENT_H