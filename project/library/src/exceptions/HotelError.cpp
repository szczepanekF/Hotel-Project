#include "exceptions/HotelError.h"

HotelError::HotelError(const std::string &arg) : logic_error(arg) {}


std::string HotelError::information() const {

    return what();

}
