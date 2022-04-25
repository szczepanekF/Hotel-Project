#include "model/Moped.h"

Moped::Moped(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice,
             const unsigned int &engineDisplacement) : MotorVehicle(initialPlateNUmber, initialBasePrice,
                                                                    engineDisplacement) {}
