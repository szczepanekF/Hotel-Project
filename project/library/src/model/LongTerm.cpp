#include "model/LongTerm.h"
#include "model/ClientType.h"

LongTerm::LongTerm() = default;

LongTerm::~LongTerm() = default;

unsigned int LongTerm::getMaxDays() const {
    return 30;
}

bool LongTerm::applyDiscount() const {
    return true;
}

std::string LongTerm::getClientTypeInfo() const {
    return "Diamond account";
}
