#ifndef HOTELPROJECT_ROOMERROR_H
#define HOTELPROJECT_ROOMERROR_H
#include "HotelError.h"

class RoomError : public HotelError{
public:
    explicit RoomError(const std::string &arg);

    ~RoomError() = default;
};


#endif //HOTELPROJECT_ROOMERROR_H
