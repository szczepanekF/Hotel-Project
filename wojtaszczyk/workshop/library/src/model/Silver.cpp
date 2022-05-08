#include "model/Silver.h"

unsigned int Silver::getMaxVehilces() const {
    return 3;
}

double Silver::applyDiscount(double price) const {
    return 6;
}

std::string Silver::getTypeInfo() const {
    return "SILVER";
}
