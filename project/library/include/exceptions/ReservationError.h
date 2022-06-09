//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_RESERVATIONERROR_H
#define HOTELPROJECT_RESERVATIONERROR_H
#include "HotelError.h"

class ReservationError : public HotelError{
public:
    explicit ReservationError(const std::string &arg);

    ~ReservationError() override;
};


#endif //HOTELPROJECT_RESERVATIONERROR_H
