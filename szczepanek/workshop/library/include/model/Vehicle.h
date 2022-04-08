//
// Created by student on 04.04.2022.
//

#ifndef CARRENTAL_VEHICLE_H
#define CARRENTAL_VEHICLE_H
#include <string>

class Vehicle {
private:
    std::string plateNumber;
    unsigned int basePrice;
    bool rented=false;

public:
    Vehicle(const std::string &init_plateNumber,const unsigned int &init_basePrice);

    const std::string getVehicleInfo() const;


    const std::string &get_plateNumber() const;
    const unsigned int &get_basePrice() const;
    const bool &isRented() const;

    void set_plateNumber(std::string const new_plateNumber);
    void set_basePrice(unsigned int const new_basePrice);
    void set_rented(bool const new_rented);

};

#endif //CARRENTAL_VEHICLE_H
