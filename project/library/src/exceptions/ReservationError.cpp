#include "exceptions/ReservationError.h"

ReservationError::ReservationError(const std::string &arg) : HotelError(arg) {}

ReservationError::~ReservationError() = default;
