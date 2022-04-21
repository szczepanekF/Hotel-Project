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
    bool archive=false;

public:
    Vehicle(const std::string &init_plateNumber,const unsigned int &init_basePrice);
    virtual ~Vehicle()=0;
    virtual const std::string getVehicleInfo() const;


    const std::string &get_plateNumber() const;
    const unsigned int &get_basePrice() const;
    const bool &isArchive() const;

    void set_plateNumber(std::string const &new_plateNumber);
    void set_basePrice(unsigned int const &new_basePrice);
    void set_archive(bool const &new_archive);


    virtual double get_ActualRentalPrice() const;
};

#endif //CARRENTAL_VEHICLE_H
