#ifndef CARRENTAL_TYPEDEF_H
#define CARRENTAL_TYPEDEF_H
#include <memory>
#include <functional>

class Vehicle;
class Client;
class Address;
class Rent;
class StorageContainer;
class Bicycle;
class MotorVehicle;
class Moped;
class Car;
class ClientType;
class Default;
class Gold;
class Silver;
class Bronze;
class Platinum;
class Diamond;
class ClientRepository;
class VehicleRepository;
class RentRepository;


typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::shared_ptr<StorageContainer> StorageContainerPtr;
typedef std::shared_ptr<Moped> MopedPtr;
typedef std::shared_ptr<Car> CarPtr;
typedef std::shared_ptr<MotorVehicle> MotorVehiclePtr;
typedef std::shared_ptr<Bicycle> BicyclePtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Default> DefaultPtr;
typedef std::shared_ptr<Bronze> BronzePtr;
typedef std::shared_ptr<Silver> SilverPtr;
typedef std::shared_ptr<Gold> GoldPtr;
typedef std::shared_ptr<Platinum> PlatinumPtr;
typedef std::shared_ptr<Diamond> DiamondPtr;
typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::shared_ptr<VehicleRepository> VehicleRepositoryPtr;
typedef std::shared_ptr<RentRepository> RentRepositoryPtr;

typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(VehiclePtr)> VehiclePredicate;
typedef std::function<bool(RentPtr)> RentPredicate;


#endif //CARRENTAL_TYPEDEF_H
