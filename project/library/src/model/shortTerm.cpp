//
// Created by student on 21.05.2022.
//

#include "model/shortTerm.h"

shortTerm::~shortTerm() = default;

unsigned int shortTerm::getMaxDays() const {
    return 2;
}

bool shortTerm::applyDiscount() const {
    return false;
}

std::string shortTerm::getClientTypeInfo() const {
    return "Short Term Client";
}

shortTerm::shortTerm() = default;
