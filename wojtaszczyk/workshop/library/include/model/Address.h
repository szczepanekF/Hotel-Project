
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

    std::string GetAddressInfo() const;
    const std::string &GetAddresscity() const;
    const std::string &GetAddressstreet() const;
    const std::string &GetAddressnumber() const;



};

#endif //CARRENTAL_ADDRESS_H
