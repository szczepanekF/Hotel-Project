#include "model/Address.h"
#include <iostream>

using namespace std;

     Address::Address(const string &init_city,const string &init_street,const string &init_number)
        :city(init_city),street(init_street),number(init_number)
     {}

    std::string Address::getAddressInfo()
    {
         return "Address: "+ city + ", st: " + street + ", nr: " + number;
    }

    const std::string &Address::get_city() const
    {
         return city;
    }

    const std::string &Address::get_street() const
    {
        return street;
    }

    const std::string &Address::get_number() const
    {
        return number;
    }
/*
    void Address::set_city(std::string new_city)
    {
         city = new_city;
    }

    void Address::set_street(std::string new_street)
    {
        street = new_street;
    }

    void Address::set_number(std::string new_number)
    {
        number = new_number;
    }*/