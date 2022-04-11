
#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>
#include <iostream>
#include <vector>


class Rent;
class Address;
class Rent;

class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    Address*  ClientAddress;
    std::vector <Rent*> currentRents;
    Client();
public:
    std::string GetClientInfo() const;
    Client(const std::string &Initial_FirstName, const std::string &Initial_LastName, const std::string &Initial_PersonalID,Address* Initial_adres);
    ~Client();
    const std::string &GetClientFirstName() const;
    const std::string &GetClientLastName() const;
    const std::string &GetClientPersonalID() const;
    Address* GetClientAddress() const;
    void SetClientFirstName(const std::string &Changed_FirstName);
    void SetClientLastName(const std::string &Changed_LastName);
    void SetClientAddress(Address* ChangedAddress );
    void AddNewRent(Rent* NewRent);
    unsigned int GetClient_RentNumber() const;
    Rent* GetClientRent(const unsigned int &i) const;
    void GetFullClientInfo() const;
    void removeClientRent(Rent *rent);
};




#endif //CARRENTAL_CLIENT_H
