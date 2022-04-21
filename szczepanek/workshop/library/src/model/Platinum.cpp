#include "model/Platinum.h"

const double Platinum::applyDiscount(const double &price) const {
    return 0.10*price;
}

const unsigned int Platinum::getMaxVehicles() const {
    return 5;
}

std::string Platinum::getTypeInfo() const {
    return "Type: Platinum";
}

Platinum::~Platinum() {

}
