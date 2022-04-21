#include "model/Car.h"

using namespace std;

Car::Car(const std::string &initPlateNumber, const unsigned int &initBasePrice,
         const unsigned int &init_engineDisplacement,const SegmentType &init_segment)
 : MotorVehicle(initPlateNumber,initBasePrice,init_engineDisplacement),segment(init_segment)
{

}

Car::~Car() {}

double Car::get_ActualRentalPrice() const {
    return MotorVehicle::get_ActualRentalPrice()*segment/10.0;
}

const std::string Car::getVehicleInfo() const
{
    string info;
    info = "Car " + Vehicle::getVehicleInfo() + ", segment " + to_string(segment);
    return info;
}