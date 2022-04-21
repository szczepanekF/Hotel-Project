//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_SILVER_H
#define CARRENTAL_SILVER_H
#include "ClientType.h"

class Silver:public ClientType{
public:
    virtual ~Silver() ;
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string getTypeInfo() const override;
};

#endif //CARRENTAL_SILVER_H
