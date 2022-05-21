#include "model/Vehicle.h"


Vehicle::Vehicle(const std::string &Initial_plateNUmber,const unsigned int &Initial_basePrice)
try:plateNumber(Initial_plateNUmber),basePrice(Initial_basePrice){
    if(Initial_plateNUmber.empty()){
        throw VehicleException("empty PlateNumber Error");
    }
    if(Initial_basePrice<=0){
        throw VehicleException("Bad Price Error");
    }
}catch(const VehicleException &e){
    std::cout<<e.what()<<'\n';
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
    else
        throw VehicleException("Bad Argument Error");
}
void Vehicle::setVehiclebasePrcie(const unsigned int &ChangedbasePrice) {
    if(ChangedbasePrice<=0){
        throw VehicleException("Bad Price Error");
    }else
    basePrice=ChangedbasePrice;
}
double Vehicle::getActualRentalPrice() const {
    return getVehiclebasePrice();
}

Vehicle::~Vehicle() {

}

std::string Vehicle::getInfo() const {
    return getVehicleInfo();
}

const std::string &Vehicle::getId() const {
    return getVehicleplateNumber();
}
