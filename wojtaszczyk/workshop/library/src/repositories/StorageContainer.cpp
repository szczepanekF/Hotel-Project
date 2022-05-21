#include "repositories/StorageContainer.h"

StorageContainer::StorageContainer() {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;
    boost::uuids::uuid ID={1};
    ClientPtr testClient;
    VehiclePtr testVehicle;
    RentPtr testRent;
    ClientTypePtr testType;
    testType= std::make_shared<Default>();
    testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
    testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress1,testType);
    testVehicle= std::make_shared<Bicycle>(testplateNumber,testbasePrice);
    testRent=std::make_shared<Rent>(ID,testClient,testVehicle,pt::not_a_date_time);
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


}
