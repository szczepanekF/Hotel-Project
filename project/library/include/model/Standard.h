#ifndef HOTELPROJECT_STANDARD_H
#define HOTELPROJECT_STANDARD_H
#include "ClientType.h"

class Standard : public ClientType{
public:
    ~Standard() override;
    int getMaxDays() const override;
    bool applyDiscount() const override;
    std::string getClientTypeInfo() const override;
    Standard();
};


#endif //HOTELPROJECT_STANDARD_H
