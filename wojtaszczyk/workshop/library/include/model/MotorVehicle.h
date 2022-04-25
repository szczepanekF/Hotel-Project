#ifndef CARRENTAL_MOTORVEHICLE_H
#define CARRENTAL_MOTORVEHICLE_H
#include "Vehicle.h"

class MotorVehicle :public Vehicle{
private:
    unsigned int engineDisplacement;
public:
    MotorVehicle(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
                 const unsigned int &engineDisplacement);
    virtual double getActualRentalPrice() const override;
    virtual ~MotorVehicle()=0;
    virtual std::string getVehicleInfo() const override;
    const unsigned int &getEngineDisplacement() const;
};


#endif //CARRENTAL_MOTORVEHICLE_H
