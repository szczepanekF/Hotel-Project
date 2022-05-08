#include "model/Bronze.h"

unsigned int Bronze::getMaxVehilces() const {
    return 2;
}

double Bronze::applyDiscount(double price) const {
    return 3;
}

std::string Bronze::getTypeInfo() const {
    return "BRONZE";
}
