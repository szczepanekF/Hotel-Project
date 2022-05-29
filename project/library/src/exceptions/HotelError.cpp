//
// Created by student on 29.05.2022.
//

#include "exceptions/HotelError.h"
#include <sstream>

HotelError::HotelError(const std::string &arg) : logic_error(arg) {}

HotelError::~HotelError() {

}

std::string HotelError::information() const {

    return what();

}
