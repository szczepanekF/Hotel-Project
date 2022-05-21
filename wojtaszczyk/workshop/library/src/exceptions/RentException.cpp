#include "exceptions/RentException.h"

RentException::RentException(const std::string &arg) : logic_error(arg) {}
