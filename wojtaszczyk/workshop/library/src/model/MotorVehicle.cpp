#include "model/MotorVehicle.h"

MotorVehicle::MotorVehicle(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
                           const unsigned int &engineDisplacement) try: Vehicle(initialPlateNUmber, initialBasePrice),
                                                              engineDisplacement(engineDisplacement) {
    if (engineDisplacement <= 0) {
    throw VehicleException("Bad Engine Error");
}
}catch(const VehicleException &e){
    std::cout<<e.what()<<'\n';
}

double MotorVehicle::getActualRentalPrice() const {
    double x;
    if(engineDisplacement<1000){
        x=1.0;
    }
    else if(engineDisplacement>2000){
        x=1.5;
    }
    else{
        x=engineDisplacement/2000.0+0.5;
    }

    return Vehicle::getActualRentalPrice()*x;
}

MotorVehicle::~MotorVehicle() {

}

std::string MotorVehicle::getVehicleInfo() const {
    return Vehicle::getVehicleInfo()+" "+ std::to_string(getEngineDisplacement());
}

const unsigned int &MotorVehicle::getEngineDisplacement() const {
    return engineDisplacement;
}
