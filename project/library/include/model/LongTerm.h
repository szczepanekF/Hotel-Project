#ifndef HOTELPROJECT_LONGTERM_H
#define HOTELPROJECT_LONGTERM_H
#include "ClientType.h"


class LongTerm : public ClientType{
public:
    LongTerm();
    ~LongTerm() override;
    unsigned int getMaxDays() const override;
    bool applyDiscount() const override;
    std::string getClientTypeInfo() const override;
};


#endif //HOTELPROJECT_LONGTERM_H
