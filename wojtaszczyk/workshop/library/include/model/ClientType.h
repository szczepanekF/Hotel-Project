#ifndef CARRENTAL_CLIENTTYPE_H
#define CARRENTAL_CLIENTTYPE_H
#include "Client.h"

class ClientType {
public:
    virtual unsigned int getMaxVehilces() const;
    virtual double applyDiscount(double price) const;
    virtual std::string getTypeInfo() const;
    virtual ~ClientType()=0;

};


#endif //CARRENTAL_CLIENTTYPE_H
