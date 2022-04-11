#include "model/Vehicle.h"

Vehicle::Vehicle(const std::string &Initial_plateNUmber,const unsigned int &Initial_basePrice)
:plateNumber(Initial_plateNUmber),basePrice(Initial_basePrice){
}

 std::string Vehicle::GetVehicleInfo() const {
    return std::to_string(basePrice)+" "+plateNumber;
}
const unsigned int &Vehicle::GetVehiclebasePrice() const {
    return basePrice;
}
const std::string &Vehicle::GetVehicleplateNumber() const {
    return plateNumber;
}
void Vehicle::SetVehicleplateNumber(const std::string &ChangedplateNumber) {
    if (ChangedplateNumber!="")
        plateNumber=ChangedplateNumber;
}
void Vehicle::SetVehiclebasePrcie(const unsigned int &ChangedbasePrice) {
    basePrice=ChangedbasePrice;
}

bool Vehicle::isRetend() const {
    return retend;
}
void Vehicle::setRetend(bool changedretend) {
    Vehicle::retend = changedretend;
}