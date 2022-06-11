#include "model/Standard.h"

Standard::~Standard() = default;

unsigned int Standard::getMaxDays() const {
    return 7;
}

bool Standard::applyDiscount() const {
    return true;
}

std::string Standard::getClientTypeInfo() const {
    return "Standard Client";
}

Standard::Standard() = default;
