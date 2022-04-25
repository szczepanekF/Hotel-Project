

#ifndef CARRENTAL_TYPEDEF_H
#define CARRENTAL_TYPEDEF_H

class Vehicle;
class Client;
class Address;
class Rent;
class StorageContainer;


typedef Client* ClientPtr;
typedef Rent* RentPtr;
typedef Address* AddressPtr;
typedef Vehicle* VehiclePtr;
typedef StorageContainer* StorageContainerPtr;
typedef bool (*ClientPredicate)(ClientPtr);
typedef bool (*VehiclePredicate)(VehiclePtr);
typedef bool (*RentPredicate)(RentPtr);


#endif //CARRENTAL_TYPEDEF_H
