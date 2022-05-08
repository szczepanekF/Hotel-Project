#include "model/Vehicle.h"


Vehicle::Vehicle(const std::string &Initial_plateNUmber,const unsigned int &Initial_basePrice)
:plateNumber(Initial_plateNUmber),basePrice(Initial_basePrice){
}

 std::string Vehicle::getVehicleInfo() const {
    return std::to_string(basePrice)+" "+plateNumber;
}
const unsigned int &Vehicle::getVehiclebasePrice() const {
    return basePrice;
}
const std::string &Vehicle::getVehicleplateNumber() const {
    return plateNumber;
}
void Vehicle::setVehicleplateNumber(const std::string &ChangedplateNumber) {
    if (ChangedplateNumber!="")
        plateNumber=ChangedplateNumber;
}
void Vehicle::setVehiclebasePrcie(const unsigned int &ChangedbasePrice) {
    basePrice=ChangedbasePrice;
}
double Vehicle::getActualRentalPrice() const {
    return getVehiclebasePrice();
}

Vehicle::~Vehicle() {

}
