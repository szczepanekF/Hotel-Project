#include <string>
#include "model/Bicycle.h"

using namespace std;

Bicycle::Bicycle(const std::string &initPlateNumber, const unsigned int &initBasePrice)
    :Vehicle(initPlateNumber, initBasePrice)
{


}

Bicycle::~Bicycle() {}

double Bicycle::get_ActualRentalPrice() const
{
    return Vehicle::get_ActualRentalPrice();
}

const string Bicycle::getVehicleInfo() const
{
    string info;
    info = "Bicycle: "+Vehicle::getVehicleInfo();
    return info;
}