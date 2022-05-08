#ifndef CARRENTAL_DIAMOND_H
#define CARRENTAL_DIAMOND_H
#include "ClientType.h"

class Diamond :public ClientType{
public:
    unsigned int getMaxVehilces() const override;

    double applyDiscount(double price) const override;

    std::string getTypeInfo() const override;
};


#endif //CARRENTAL_DIAMOND_H
