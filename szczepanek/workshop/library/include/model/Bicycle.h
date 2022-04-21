//
// Created by student on 15.04.2022.
//

#ifndef CARRENTAL_BICYCLE_H
#define CARRENTAL_BICYCLE_H

#include <string>
#include "Vehicle.h"
class Bicycle : public Vehicle{
public:
    Bicycle(const std::string &initPlateNumber, const unsigned int &initBasePrice);
    virtual ~Bicycle();
    virtual double get_ActualRentalPrice() const override;
    virtual const std::string getVehicleInfo() const override;
};
#endif //CARRENTAL_BICYCLE_H
