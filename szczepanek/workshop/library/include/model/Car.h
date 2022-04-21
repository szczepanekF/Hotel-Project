//
// Created by student on 15.04.2022.
//

#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include "MotorVehicle.h"
enum SegmentType{
    A=10,
    B=11,
    C=12,
    D=13,
    E=15
};

class Car : public MotorVehicle{
private:
    SegmentType segment;
public:
    Car(const std::string &initPlateNumber, const unsigned int &initBasePrice,const unsigned int &init_engineDisplacement,const SegmentType &init_segment);
    virtual ~Car() override;
    virtual double get_ActualRentalPrice() const override;
    virtual const std::string getVehicleInfo() const override;

};


#endif //CARRENTAL_CAR_H
