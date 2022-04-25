#include "repositories/StorageContainer.h"

StorageContainer::StorageContainer() {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    const unsigned int ID=11;
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;
    ClientPtr testClient;
    VehiclePtr testVehicle;
    RentPtr testRent;
    testaddress1 = new Address("London", "Accacia Avenue", "22");
    testClient= new Client(testFirstName, testLastName, testPersonalID, testaddress1);
    testVehicle= new Bicycle(testplateNumber,testbasePrice);
    testRent=new Rent(1,testClient,testVehicle,pt::not_a_date_time);
    clientRepository.add(testClient);
    vehicleRepository.add(testVehicle);
    rentRepository.add(testRent);
}

 ClientRepository &StorageContainer::getClientRepository()  {
    return clientRepository;
}

 VehicleRepository &StorageContainer::getVehicleRepository()  {
    return vehicleRepository;
}

 RentRepository &StorageContainer::getRentRepository()  {
    return rentRepository;
}

StorageContainer::~StorageContainer() {
AddressPtr a=getClientRepository().get(0)->getClientAddress();
delete a;
}
