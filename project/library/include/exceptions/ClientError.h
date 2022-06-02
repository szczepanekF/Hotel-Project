//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_CLIENTERROR_H
#define HOTELPROJECT_CLIENTERROR_H
#include "HotelError.h"

class ClientError :public HotelError{
public:
    ClientError(const std::string &arg);
    virtual ~ClientError();
};


#endif //HOTELPROJECT_CLIENTERROR_H
