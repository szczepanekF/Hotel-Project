#include "exceptions/RoomError.h"

RoomError::RoomError(const std::string &arg) : HotelError(arg) {}

RoomError::~RoomError() = default;
