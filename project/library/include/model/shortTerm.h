#ifndef HOTELPROJECT_SHORTTERM_H
#define HOTELPROJECT_SHORTTERM_H
#include "ClientType.h"

class shortTerm: public ClientType{
public:
    shortTerm();
    ~shortTerm() override;
    int getMaxDays() const override;
    bool applyDiscount() const override;
    std::string getClientTypeInfo() const override;
};


#endif //HOTELPROJECT_SHORTTERM_H
