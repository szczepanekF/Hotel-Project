//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_DIAMOND_H
#define CARRENTAL_DIAMOND_H
#include "ClientType.h"

class Diamond:public ClientType{
public:
    virtual ~Diamond();
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string getTypeInfo() const override;
};

#endif //CARRENTAL_DIAMOND_H
