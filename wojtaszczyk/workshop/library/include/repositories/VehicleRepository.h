#ifndef CARRENTAL_VEHICLEREPOSITORY_H
#define CARRENTAL_VEHICLEREPOSITORY_H
#include "../model/Bicycle.h"
#include "Repository.h"

class VehicleRepository :public Repository<Vehicle,VehicleException>{

};

bool allVehiclepredicate(const VehiclePtr ptr);
bool vehiclebaseprice25(const VehiclePtr ptr);
#endif //CARRENTAL_VEHICLEREPOSITORY_H
