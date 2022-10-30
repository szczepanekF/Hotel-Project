#ifndef HOTELPROJECT_ROOMERROR_H
#define HOTELPROJECT_ROOMERROR_H
#include "HotelError.h"

class RoomError : public HotelError{
public:
    explicit RoomError(const std::string &arg);

    ~RoomError() override;
};


#endif //HOTELPROJECT_ROOMERROR_H
