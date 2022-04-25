#ifndef CARRENTAL_STORAGECONTAINER_H
#define CARRENTAL_STORAGECONTAINER_H
#include "VehicleRepository.h"
#include "RentRepository.h"
#include "ClientRepository.h"
#include "model/Address.h"

class StorageContainer {
private:
    ClientRepository clientRepository;
    VehicleRepository  vehicleRepository;
    RentRepository rentRepository;
public:
    StorageContainer();
    ClientRepository &getClientRepository() ;
    VehicleRepository &getVehicleRepository() ;
    RentRepository &getRentRepository() ;
    virtual ~StorageContainer();
};


#endif //CARRENTAL_STORAGECONTAINER_H
