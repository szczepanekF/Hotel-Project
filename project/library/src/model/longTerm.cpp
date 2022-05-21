//
// Created by student on 21.05.2022.
//

#include "model/longTerm.h"

longTerm::longTerm() {}

longTerm::~longTerm() {

}

int longTerm::getMaxDays() const {
    return 30;
}

bool longTerm::applyDiscount() const {
    return true;
}

std::string longTerm::getClientTypeInfo() const {
    return "Long Term Client";
}
