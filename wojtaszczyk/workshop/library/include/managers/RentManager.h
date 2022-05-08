#ifndef CARRENTAL_RENTMANAGER_H
#define CARRENTAL_RENTMANAGER_H
#include "repositories/StorageContainer.h"

class RentManager {
private:
    RentRepositoryPtr currentRents;
    RentRepositoryPtr archiveRents;
public:
    std::vector<RentPtr> findAllClientRents(const ClientPtr &ptr) const;
    RentPtr findVehicleRent(const VehiclePtr &ptr) const;
    std::vector<RentPtr> findRents(RentPredicate predicate) const;
    std::vector<RentPtr> findAllRents() const;
    double checkClientRentBalance(const ClientPtr &ptr) const;
    RentPtr rentVehicle(const unsigned int &InitialID,const ClientPtr &cptr,const VehiclePtr &vptr,const pt::ptime &InitialbeginTime);
    void returnVehicle(const VehiclePtr &vptr);
    void changeClientType(const ClientPtr &ptr);

    RentManager();
};


#endif //CARRENTAL_RENTMANAGER_H
