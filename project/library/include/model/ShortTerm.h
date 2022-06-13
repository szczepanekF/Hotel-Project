#ifndef HOTELPROJECT_SHORTTERM_H
#define HOTELPROJECT_SHORTTERM_H
#include "ClientType.h"

class ShortTerm: public ClientType{
public:
    ShortTerm();
    ~ShortTerm() override;
    unsigned int getMaxDays() const override;
    bool applyDiscount() const override;
    std::string getClientTypeInfo() const override;
};


#endif //HOTELPROJECT_SHORTTERM_H
