//
// Created by student on 03.04.2022.
//


#ifndef CARRENTAL_ADDRESS_H
#define CARRENTAL_ADDRESS_H
#include <string>
class Address {

    std::string city;
    std::string street;
    std::string number;

public:

    Address(const std::string &init_city,const std::string &init_street,const std::string &init_number);


    std::string getAddressInfo();


    const std::string &get_city() const;
    const std::string &get_street() const;
    const std::string &get_number() const;
/*
    void set_city(std::string new_city);
    void set_street(std::string new_street);
    void set_number(std::string new_number);

*/
};

#endif //CARRENTAL_ADDRESS_H
