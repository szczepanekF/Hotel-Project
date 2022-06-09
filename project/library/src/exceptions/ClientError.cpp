//
// Created by student on 29.05.2022.
//

#include "exceptions/ClientError.h"

ClientError::ClientError(const std::string &arg) : HotelError(arg) {}

ClientError::~ClientError() = default;
