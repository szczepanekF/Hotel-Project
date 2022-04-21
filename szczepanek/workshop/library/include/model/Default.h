//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_DEFAULT_H
#define CARRENTAL_DEFAULT_H
#include "ClientType.h"

class Default:public ClientType{
public:
    virtual ~Default() ;
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string  getTypeInfo() const override;
};

#endif //CARRENTAL_DEFAULT_H
