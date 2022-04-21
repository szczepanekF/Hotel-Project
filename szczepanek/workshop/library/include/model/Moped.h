//
// Created by student on 15.04.2022.
//

#ifndef CARRENTAL_MOPED_H
#define CARRENTAL_MOPED_H
#include "MotorVehicle.h"

class Moped : public MotorVehicle
{
public:
    Moped(const std::string &initPlateNumber, const unsigned int &initBasePrice,const unsigned int &init_engineDisplacement);
    virtual ~Moped() override;
    virtual double get_ActualRentalPrice() const override;
    virtual const std::string getVehicleInfo() const override;
};

#endif //CARRENTAL_MOPED_H
