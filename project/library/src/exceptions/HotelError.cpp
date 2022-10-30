#include "exceptions/HotelError.h"

HotelError::HotelError(const std::string &arg) : logic_error(arg) {}

HotelError::~HotelError() = default;

std::string HotelError::information() const {

    return what();

}
