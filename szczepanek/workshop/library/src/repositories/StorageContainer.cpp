#include "repositories/StorageContainer.h"
#include "model/Bicycle.h"
#include "model/Default.h"
#include <memory>


StorageContainer::StorageContainer()
{

    AddressPtr ad1 = std::make_shared<Address>("Łask","Rogaczewska","4");
    ClientTypePtr ct1 = std::make_shared<Default>();
    ClientPtr c1=std::make_shared<Client>("Filip", "Szczepanek", "242544",ad1,ct1);
    VehiclePtr veh1=std::make_shared<Bicycle>("FAJFUS", 5000);
    RentPtr ren1=std::make_shared<Rent>(1,c1,veh1,pt::not_a_date_time);

    AddressPtr ad2=std::make_shared<Address>("Pabianice","Dobra","25");
    ClientPtr c2=std::make_shared<Client>("Milosz", "Wojtaszczyk", "242567",ad2,ct1);
    VehiclePtr veh2=std::make_shared<Bicycle>("DISOWUZ", 10000);
    RentPtr rent2=std::make_shared<Rent>(2,c2,veh2,pt::second_clock::local_time()-pt::minutes(30));

    clientRep.add_client(c1);
    vehicleRep.add_vehicle(veh1);
    rentRep.add_rent(ren1);

    clientRep.add_client(c2);
    vehicleRep.add_vehicle(veh2);
    rentRep.add_rent(rent2);

}
StorageContainer::~StorageContainer() {
//    delete get_clientRepository().get_client(0)->get_address();
//    delete get_clientRepository().get_client(1)->get_address();
}
ClientRepository &StorageContainer::get_clientRepository()
{
    return clientRep;
}

VehicleRepository &StorageContainer::get_vehicleRepository()
{
    return vehicleRep;
}
RentRepository &StorageContainer::get_rentRepository()
{
    return rentRep;
}