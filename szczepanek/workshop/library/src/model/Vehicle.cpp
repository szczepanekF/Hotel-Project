//
// Created by student on 04.04.2022.
//
#include "model/Vehicle.h"
#include <iostream>

using namespace std;
    Vehicle::Vehicle(const string &init_plateNumber, const unsigned int &init_basePrice)
        :plateNumber(init_plateNumber),basePrice(init_basePrice)
    {

    }

    const string Vehicle::getVehicleInfo() const
    {
        return "Vehicle: plate number: " + plateNumber + ", price: " + to_string(basePrice);
    }
    const string &Vehicle::get_plateNumber() const
    {
        return plateNumber;
    }
    const unsigned int &Vehicle::get_basePrice() const
    {
        return basePrice;
    }

    const bool &Vehicle::isRented() const
    {
        return rented;
    }


    void Vehicle::set_plateNumber(const string new_plateNumber)
    {
        if(new_plateNumber.compare("")!=0)
            plateNumber = new_plateNumber;
    }

    void Vehicle::set_basePrice(const unsigned int new_basePrice)
    {
        basePrice = new_basePrice;
    }
    void Vehicle::set_rented(bool const new_rented)
    {
        rented = new_rented;
    }