#ifndef HOTELPROJECT_CLIENTTYPE_H
#define HOTELPROJECT_CLIENTTYPE_H
#include <string>

class ClientType {
public:
    ClientType();
    virtual ~ClientType();
    virtual int getMaxDays() const=0;
    virtual bool applyDiscount() const=0;
    virtual std::string getClientTypeInfo() const=0;
};


#endif //HOTELPROJECT_CLIENTTYPE_H
