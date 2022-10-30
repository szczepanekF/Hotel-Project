#include "exceptions/ClientError.h"

ClientError::ClientError(const std::string &arg) : HotelError(arg) {}

ClientError::~ClientError() = default;
