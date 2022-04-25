#ifndef CARRENTAL_BICYCLE_H
#define CARRENTAL_BICYCLE_H
#include "Vehicle.h"

class Bicycle : public Vehicle{
private:
public:
    Bicycle(const std::string &initialPlateNUmber, const unsigned int &initialBasePrice);
};


#endif //CARRENTAL_BICYCLE_H
