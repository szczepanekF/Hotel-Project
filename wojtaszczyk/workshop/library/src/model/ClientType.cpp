#include "model/ClientType.h"

ClientType::~ClientType() {

}

unsigned int ClientType::getMaxVehilces() const {
    return 1;
}

double ClientType::applyDiscount(double price) const {
    return 0;
}

std::string ClientType::getTypeInfo() const {
    return "DEFAULT";
}
