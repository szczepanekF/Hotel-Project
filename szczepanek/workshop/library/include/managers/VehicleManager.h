//
// Created by student on 20.04.2022.
//

#ifndef CARRENTAL_VEHICLEMANAGER_H
#define CARRENTAL_VEHICLEMANAGER_H
#include "repositories/VehicleRepository.h"
#include "model/Car.h"
class VehicleManager{
    VehicleRepository vehicleRepository;
public:

    VehiclePtr getVehicle(const std::string &plateNumber) const;


    VehiclePtr registerBicycle(const std::string &initPlateNumber, const unsigned int &initBasePrice);
    VehiclePtr registerMoped(const std::string &initPlateNumber, const unsigned int &initBasePrice,const unsigned int &init_engineDisplacement);
    VehiclePtr registerCar(const std::string &initPlateNumber, const unsigned int &initBasePrice,const unsigned int &init_engineDisplacement,const SegmentType &init_segment);


    void unregisterVehicle(VehiclePtr vehicleptr);
    std::vector<VehiclePtr> findVehicles(VehiclePredicate predicate) const;
};
#endif //CARRENTAL_VEHICLEMANAGER_H
