//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_HOTELERROR_H
#define HOTELPROJECT_HOTELERROR_H
#include <memory>

class HotelError : public std::logic_error{
public:
    HotelError(const std::string &arg);
    virtual std::string information() const;
    virtual ~HotelError();
};


#endif //HOTELPROJECT_HOTELERROR_H
