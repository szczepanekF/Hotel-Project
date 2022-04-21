#include "model/Diamond.h"

const double Diamond::applyDiscount(const double &price) const {
    if(price <=125 && price>0)
        return 0.10*price;
    else if(price<=250)
        return 0.20*price;
    else if(price<=500)
        return 0.30*price;
    else
        return 0.40*price;
}

const unsigned int Diamond::getMaxVehicles() const {
    return 10;
}
std::string Diamond::getTypeInfo() const {
    return "Type: Diamond";
}

Diamond::~Diamond() {

}
