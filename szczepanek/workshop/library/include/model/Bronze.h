//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_BRONZE_H
#define CARRENTAL_BRONZE_H
#include "ClientType.h"

class Bronze:public ClientType{
public:
    virtual ~Bronze() ;
    const unsigned int getMaxVehicles() const override;
    const double applyDiscount(const double &price) const override;
    std::string getTypeInfo() const override;
};

#endif //CARRENTAL_BRONZE_H
