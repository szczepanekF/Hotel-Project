//
// Created by student on 17.03.2022.
//

#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include "Address.h"
#include "Rent.h"
#include <vector>

class Rent;
class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    Address *address;
    std::vector<Rent *> currentRents;
    Client();
public:

    Client(const std::string &Initial_FirstName,const std::string &Initial_LastName,const std::string &Initial_PersonalID,Address *init_address);
    ~Client();

    std::string getClientInfo();
    void getFullClientInfo();

    const std::string &getfirstName() const;
    const std::string &getlastName() const;
    const std::string &getpersonalID() const;

    const Address *get_address() const;

    const unsigned int get_rentNumber() const;
    const Rent *get_currentRent(unsigned int i) const;

    void remove_currentRent(Rent * rent);

    void setfirstName(std::string const &Changed_FirstName);
    void setlastName(std::string const &Changed_LastName);
    void set_address(Address *new_address);
    void AddRent(Rent *new_rent);

    };
#endif //CARRENTAL_CLIENT_H