//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_PLATINUM_H
#define CARRENTAL_PLATINUM_H
#include "ClientType.h"

class Platinum:public ClientType{
public:
    virtual ~Platinum() ;
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string getTypeInfo() const override;
};

#endif //CARRENTAL_PLATINUM_H
