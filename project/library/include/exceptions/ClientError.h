//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_CLIENTERROR_H
#define HOTELPROJECT_CLIENTERROR_H
#include "HotelError.h"

class ClientError :public HotelError{
public:
    explicit ClientError(const std::string &arg);
    ~ClientError() override;
};


#endif //HOTELPROJECT_CLIENTERROR_H
