//
// Created by student on 08.04.2022.
//

#ifndef CARRENTAL_STORAGECONTAINER_H
#define CARRENTAL_STORAGECONTAINER_H

#include "ClientRepository.h"
#include "VehicleRepository.h"
#include "RentRepository.h"


class StorageContainer{
private:
    ClientRepository clientRep;
    VehicleRepository vehicleRep;
    RentRepository rentRep;
public:
    StorageContainer();
    ~StorageContainer();
    ClientRepository &get_clientRepository();
    VehicleRepository &get_vehicleRepository();
    RentRepository &get_rentRepository();


};

#endif //CARRENTAL_STORAGECONTAINER_H
