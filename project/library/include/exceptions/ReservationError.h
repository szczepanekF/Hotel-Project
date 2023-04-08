#ifndef HOTELPROJECT_RESERVATIONERROR_H
#define HOTELPROJECT_RESERVATIONERROR_H
#include "HotelError.h"

class ReservationError : public HotelError{
public:
    explicit ReservationError(const std::string &arg);

    ~ReservationError() = default;
};


#endif //HOTELPROJECT_RESERVATIONERROR_H
