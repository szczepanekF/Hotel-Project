#include "model/Platinum.h"

unsigned int Platinum::getMaxVehilces() const {
    return 5;
}

double Platinum::applyDiscount(double price) const {
    return price*0.1;
}

std::string Platinum::getTypeInfo() const {
    return "PLATINUM";
}
