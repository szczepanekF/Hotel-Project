#ifndef CARRENTAL_BRONZE_H
#define CARRENTAL_BRONZE_H
#include "ClientType.h"

class Bronze :public ClientType{
public:

    unsigned int getMaxVehilces() const override;
    double applyDiscount(double price) const override;
    std::string getTypeInfo() const override;
};


#endif //CARRENTAL_BRONZE_H
