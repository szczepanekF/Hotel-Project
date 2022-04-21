

#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H
//#include "model/Client.h"
#include <memory>
#include <functional>

class Client;
class Address;
class Vehicle;
class Rent;
class ClientRepository;
class VehicleRepository;
class RentRepository;
class StorageContainer;
class ClientType;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::shared_ptr<Rent> RentPtr;

typedef std::shared_ptr<ClientType> ClientTypePtr;

typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::shared_ptr<VehicleRepository> VehicleRepositoryPtr;
typedef std::shared_ptr<RentRepository> RentRepositoryPtr;
typedef std::shared_ptr<StorageContainer> StorageContainerPtr;


typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(VehiclePtr)> VehiclePredicate;
typedef std::function<bool(RentPtr)> RentPredicate;





#endif //CARRENTAL_TYPEDEFS_H
