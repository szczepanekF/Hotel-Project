#include "model/ShortTerm.h"

ShortTerm::~ShortTerm() = default;

unsigned int ShortTerm::getMaxDays() const {
    return 2;
}

bool ShortTerm::applyDiscount() const {
    return false;
}

std::string ShortTerm::getClientTypeInfo() const {
    return "Base account";
}

ShortTerm::ShortTerm() = default;
