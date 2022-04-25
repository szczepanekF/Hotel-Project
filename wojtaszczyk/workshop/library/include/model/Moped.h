#ifndef CARRENTAL_MOPED_H
#define CARRENTAL_MOPED_H
#include "MotorVehicle.h"

class Moped :public MotorVehicle{
private:
public:
    Moped(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
          const unsigned int &engineDisplacement);
};


#endif //CARRENTAL_MOPED_H
