//
// Created by student on 08.04.2022.
//

#ifndef CARRENTAL_VEHICLEREPOSITORY_H
#define CARRENTAL_VEHICLEREPOSITORY_H
//#include "../model/Vehicle.h"
#include <vector>
#include "typedefs.h"
#include <string>

class VehicleRepository {
private:
    std::vector<VehiclePtr> vehicleList;

public:

    ~VehicleRepository();
    VehiclePtr get_vehicle(unsigned int i) const;

    void add_vehicle(VehiclePtr const new_Vehicle);

    void remove_vehicle(VehiclePtr rm_Vehicle);
    const std::string report_vehicleList() const;

    const unsigned int size_vehicleList() const;

    std::vector<VehiclePtr> findBy(VehiclePredicate predicate) const;

    std::vector<VehiclePtr> findAll()const;
    VehiclePtr findByPlateNumber(const std::string &plateNumber) const;
};
#endif //CARRENTAL_VEHICLEREPOSITORY_H
