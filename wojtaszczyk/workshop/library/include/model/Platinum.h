#ifndef CARRENTAL_PLATINUM_H
#define CARRENTAL_PLATINUM_H
#include "ClientType.h"

class Platinum : public ClientType{
public:
    unsigned int getMaxVehilces() const override;
    double applyDiscount(double price) const override;
    std::string getTypeInfo() const override;
};


#endif //CARRENTAL_PLATINUM_H
