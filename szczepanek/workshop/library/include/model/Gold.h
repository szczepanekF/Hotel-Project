//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_GOLD_H
#define CARRENTAL_GOLD_H
#include "ClientType.h"

class Gold:public ClientType{
public:
    virtual ~Gold() ;
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string getTypeInfo() const override;
};

#endif //CARRENTAL_GOLD_H
