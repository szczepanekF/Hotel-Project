#include "exceptions/VehicleException.h"

VehicleException::VehicleException(const std::string &arg) : logic_error(arg) {}
