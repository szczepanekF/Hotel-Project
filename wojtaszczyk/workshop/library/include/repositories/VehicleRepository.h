#ifndef CARRENTAL_VEHICLEREPOSITORY_H
#define CARRENTAL_VEHICLEREPOSITORY_H
#include "../model/Bicycle.h"

class VehicleRepository {
private:
    std::vector<VehiclePtr> VehicleRepo;
public:
    VehiclePtr get(const unsigned int &i) const;
    void add(VehiclePtr vehicle);
    void remove(VehiclePtr vehicle);
    std::string report() const;
    unsigned int size() const;
    virtual ~VehicleRepository();
    std::vector<VehiclePtr> findBy(VehiclePredicate predicate) const;
    std::vector<VehiclePtr> findAll() const;
};

bool allVehiclepredicate(const VehiclePtr ptr);
bool vehiclebaseprice25(const VehiclePtr ptr);
#endif //CARRENTAL_VEHICLEREPOSITORY_H
