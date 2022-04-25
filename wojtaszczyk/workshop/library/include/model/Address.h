
#ifndef CARRENTAL_ADDRESS_H
#define CARRENTAL_ADDRESS_H
#include <iostream>


class Address{
private:
    std::string city;
    std::string street;
    std::string number;
public:
    Address(const std::string &Initialcity, const std::string &Initialstreet, const std::string &Initialnumber);

    std::string getAddressInfo() const;
    const std::string &getAddresscity() const;
    const std::string &getAddressstreet() const;
    const std::string &getAddressnumber() const;



};

#endif //CARRENTAL_ADDRESS_H
