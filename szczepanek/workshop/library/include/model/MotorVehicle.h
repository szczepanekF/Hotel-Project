//
// Created by student on 15.04.2022.
//

#ifndef CARRENTAL_MOTORVEHICLE_H
#define CARRENTAL_MOTORVEHICLE_H
#include "Vehicle.h"
class MotorVehicle : public Vehicle
{
private:
    unsigned int engineDisplacement;

public:
    MotorVehicle(const std::string &initPlateNumber, const unsigned int &initBasePrice,const unsigned int &init_engineDisplacement);
    virtual ~MotorVehicle()=0;
//    const unsigned int &get_engineDisplacement() const;
//    void set_engineDisplacement(unsigned int const &new_engineDisplacement);

    virtual double get_ActualRentalPrice() const override;

    virtual const std::string getVehicleInfo() const override;
};
#endif //CARRENTAL_MOTORVEHICLE_H
