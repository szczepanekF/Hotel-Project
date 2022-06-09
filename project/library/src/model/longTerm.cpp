//
// Created by student on 21.05.2022.
//

#include "model/longTerm.h"
#include "model/ClientType.h"

longTerm::longTerm() = default;

longTerm::~longTerm() = default;

unsigned int longTerm::getMaxDays() const {
    return 30;
}

bool longTerm::applyDiscount() const {
    return true;
}

std::string longTerm::getClientTypeInfo() const {
    return "Long Term Client";
}
