#ifndef CARRENTAL_SILVER_H
#define CARRENTAL_SILVER_H
#include "ClientType.h"

class Silver:public ClientType {
public:
    unsigned int getMaxVehilces() const override;

    double applyDiscount(double price) const override;

    std::string getTypeInfo() const override;
};


#endif //CARRENTAL_SILVER_H
