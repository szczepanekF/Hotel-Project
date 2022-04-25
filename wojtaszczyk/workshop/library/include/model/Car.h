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


class Car: public MotorVehicle{
private:
    SegmentType segment;
public:
    Car(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
        const unsigned int &engineDisplacement, SegmentType segment);
    virtual double getActualRentalPrice() const override;
    SegmentType getSegment() const;
    virtual std::string getVehicleInfo() const override;
};


#endif //CARRENTAL_CAR_H
