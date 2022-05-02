
#ifndef CARRENTAL_RENTMANAGER_H
#define CARRENTAL_RENTMANAGER_H
#include "repositories/RentRepository.h"
#include <boost/date_time.hpp>

class RentManager{
    RentRepository currentRents;
    RentRepository archiveRents;
public:
    std::vector<RentPtr> getAllClientRents(ClientPtr client) const;
    RentPtr getVehicleRent(VehiclePtr vehicle) const;
    std::vector<RentPtr> findRents(RentPredicate predicate) const;
    std::vector<RentPtr> findAllRents() const;
    unsigned int checkClientRentBalance(ClientPtr client) const;
    RentPtr rentVehicle(const unsigned int &init_id,ClientPtr init_client,VehiclePtr init_vehicle,pt::ptime init_beginTime);
    void returnVehicle(VehiclePtr vehicle);
    void changeClientType(ClientPtr client);
};

#endif //CARRENTAL_RENTMANAGER_H
