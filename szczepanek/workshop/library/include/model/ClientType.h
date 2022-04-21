//
// Created by student on 19.04.2022.
//

#ifndef CARRENTAL_CLIENTTYPE_H
#define CARRENTAL_CLIENTTYPE_H

#include <string>

class ClientType{
public:
//    virtual ~ClientType()=0;
    virtual const unsigned int getMaxVehicles()const=0;
    virtual const double applyDiscount(const double &price) const=0;
    virtual std::string getTypeInfo() const=0;
};


#endif //CARRENTAL_CLIENTTYPE_H
