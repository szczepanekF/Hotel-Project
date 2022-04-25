#include "model/Car.h"

Car::Car(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
         const unsigned int &engineDisplacement, SegmentType segment) : MotorVehicle(initialPlateNUmber,
                                                                                     initialBasePrice,
                                                                                     engineDisplacement),
                                                                        segment(segment) {}

double Car::getActualRentalPrice() const {

    double x=segment/10.0;

    return MotorVehicle::getActualRentalPrice()*x;
}

SegmentType Car::getSegment() const {
    return segment;
}

std::string Car::getVehicleInfo() const {
    char x;
    if(getSegment()!=15){
        x=getSegment()/10.0+'A'-1;}
    else {
        x='E';
    }
    return MotorVehicle::getVehicleInfo()+" "+x;
}


