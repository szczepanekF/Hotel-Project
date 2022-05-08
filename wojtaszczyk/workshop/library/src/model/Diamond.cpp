#include "model/Diamond.h"

unsigned int Diamond::getMaxVehilces() const {
    return 10;
}

double Diamond::applyDiscount(double price) const {
    double x;
    if(price>=0&&price<=125){
        x=0.1;
    }
    else if(price<=250){
        x=0.2;
    }
    else if(price<=500){
        x=0.3;
    }
    else if  (price>500){
        x=0.4;
    }
    return price*x;
}

std::string Diamond::getTypeInfo() const {
    return "DIAMOND";
}
