#include "model/Default.h"

const double Default::applyDiscount(const double &price) const {
    return 0;
}

const unsigned int Default::getMaxVehicles() const {
    return 1;
}

std::string Default::getTypeInfo() const {
    return "Type: Default";
}

Default::~Default() {

}
