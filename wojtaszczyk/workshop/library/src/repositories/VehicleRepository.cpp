#include "repositories/VehicleRepository.h"

bool allVehiclepredicate(const VehiclePtr ptr) {
    return true;
}

bool vehiclebaseprice25(const VehiclePtr ptr) {
    return ptr->getVehiclebasePrice()==25;
}
