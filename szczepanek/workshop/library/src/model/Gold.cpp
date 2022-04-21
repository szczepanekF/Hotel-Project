#include "model/Gold.h"

const double Gold::applyDiscount(const double &price) const {
    return 0.05*price;
}

const unsigned int Gold::getMaxVehicles() const {
    return 4;
}

std::string Gold::getTypeInfo() const {
    return "Type: Gold";
}

Gold::~Gold() {

}
