

#ifndef CARRENTAL_VEHICLE_H
#define CARRENTAL_VEHICLE_H
#include <iostream>


class Vehicle{
private:
    std::string plateNumber;
    unsigned int basePrice;
    bool retend = false;
public:
    Vehicle(const std::string &Initial_plateNUmber,const unsigned int &Initial_basePrice);
    const std::string &GetVehicleplateNumber() const;
    const unsigned int &GetVehiclebasePrice() const ;
    bool isRetend() const;
    void SetVehicleplateNumber(const std::string &ChangedplateNumber);
    void SetVehiclebasePrcie(const unsigned int &ChangedbasePrice);
    std::string GetVehicleInfo() const;
    void setRetend(bool changeretend);
};



#endif //CARRENTAL_VEHICLE_H
