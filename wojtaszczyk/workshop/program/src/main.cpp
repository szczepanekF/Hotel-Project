
#include "model/Client.h"
#include "model/Address.h"
#include "model/Vehicle.h"
#include "model/Rent.h"
#include <boost/date_time.hpp>
#include "repositories/StorageContainer.h"
#include "model/Car.h"
#include "model/Moped.h"

using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main()
{
    StorageContainer S;
    cout<<S.getClientRepository().report();
    cout<<S.getRentRepository().report();
    cout<<S.getVehicleRepository().report();
    AddressPtr A = new Address("Pabianice","Dobra","25");
    ClientPtr C = new Client("Milosz","Wojtaszczyk","242567",A);
    VehiclePtr car = new  Car("K1DIS",500,2500,E);
    RentPtr R = new Rent(2,C,car,pt::not_a_date_time);
    S.getVehicleRepository().add(car);
    S.getRentRepository().add(R);
    S.getClientRepository().add(C);
    cout<<S.getClientRepository().report();
    cout<<S.getRentRepository().report();
    cout<<S.getVehicleRepository().report();
    delete A;


    return 0;
}
