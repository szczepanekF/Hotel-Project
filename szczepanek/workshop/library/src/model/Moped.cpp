#include "model/Moped.h"

Moped::Moped(const std::string &initPlateNumber, const unsigned int &initBasePrice,
             const unsigned int &init_engineDisplacement)
     : MotorVehicle(initPlateNumber,initBasePrice,init_engineDisplacement)
{

}

Moped::~Moped(){}
double Moped::get_ActualRentalPrice() const
{
    return MotorVehicle::get_ActualRentalPrice();
}

const std::string Moped::getVehicleInfo() const
{
    return "Moped " + Vehicle::getVehicleInfo();
}
