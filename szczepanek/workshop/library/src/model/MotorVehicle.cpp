#include "model/MotorVehicle.h"

using namespace std;

MotorVehicle::MotorVehicle(const std::string &initPlateNumber, const unsigned int &initBasePrice,
                           const unsigned int &init_engineDisplacement)
    :Vehicle(initPlateNumber,initBasePrice),engineDisplacement(init_engineDisplacement) {


}
MotorVehicle::~MotorVehicle() throw() {}

double MotorVehicle::get_ActualRentalPrice() const
{
    double priceMultiplier=(1.0+(engineDisplacement-1000)*0.0005);


    if(engineDisplacement < 1000)
        return Vehicle::get_ActualRentalPrice()*1.0;
    else if(engineDisplacement < 2000)
        return Vehicle::get_ActualRentalPrice()*priceMultiplier;
    else
        return Vehicle::get_ActualRentalPrice()*1.5;
}

const std::string MotorVehicle::getVehicleInfo() const
{
    string info;
    info = "motorvehicle - " + Vehicle::getVehicleInfo() + ", engineDisplacement: " + to_string(engineDisplacement);
    return info;
}


//const unsigned int &MotorVehicle::get_engineDisplacement() const
//{
//    return engineDisplacement;
//}
//
//void MotorVehicle::set_engineDisplacement(const unsigned int &new_engineDisplacement)
//{
//    engineDisplacement = new_engineDisplacement;
//}