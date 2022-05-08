#include "model/Gold.h"

unsigned int Gold::getMaxVehilces() const {
    return 4;
}

double Gold::applyDiscount(double price) const {
    return price*0.05;
}

std::string Gold::getTypeInfo() const {
    return "GOLD";
}
