#ifndef HOTELPROJECT_LONGTERM_H
#define HOTELPROJECT_LONGTERM_H
#include "ClientType.h"


class longTerm :public ClientType{
public:
    longTerm();
    ~longTerm() override;
    unsigned int getMaxDays() const override;
    bool applyDiscount() const override;
    std::string getClientTypeInfo() const override;
};


#endif //HOTELPROJECT_LONGTERM_H
