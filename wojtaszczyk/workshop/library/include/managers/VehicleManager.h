#ifndef CARRENTAL_VEHICLEMANAGER_H
#define CARRENTAL_VEHICLEMANAGER_H
#include "repositories/StorageContainer.h"
#include "model/Car.h"
#include "model/Moped.h"
#include "model/Bicycle.h"

class VehicleManager {
private:
    VehicleRepositoryPtr currentVehicles;
public:
    VehiclePtr getVehicle(const std::string &Plate) const;
    VehiclePtr registerMoped(const std::string &Initial_Plate,const unsigned int & BasePrice,const unsigned int &engine);
    VehiclePtr registerBicycle(const std::string &Initial_Plate,const unsigned int & BasePrice);
    VehiclePtr registerCar(const std::string &Initial_Plate,const unsigned int & BasePrice,const unsigned int &engine,SegmentType segment);
    std::vector<VehiclePtr> findVehicles(VehiclePredicate predicate) const;
    std::vector<VehiclePtr> findAllVehicles() const;
    VehicleManager();
};


#endif //CARRENTAL_VEHICLEMANAGER_H
