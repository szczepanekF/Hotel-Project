#include "model/Client.h"
#include "model/Address.h"
#include "model/Vehicle.h"
#include "model/Rent.h"
#include <boost/date_time.hpp>
#include "repositories/StorageContainer.h"
#include "model/Car.h"
#include "model/Moped.h"
#include "managers/ClientManager.h"
#include "managers/RentManager.h"
#include "managers/VehicleManager.h"

using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main()
{
    pt::ptime empty = pt::not_a_date_time;


    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    ClientTypePtr testType;
    testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
    testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
    testType= std::make_shared<Default>();
    ClientTypePtr testType2= make_shared<Gold>();
    ClientManager CM;
    VehicleManager VM;
    RentManager RM;
    ClientPtr c1=CM.registerClient(testFirstName,testLastName,testPersonalID,testaddress1,testType2);
    ClientPtr c2= CM.registerClient("2","2","2",testaddress2,testType);
    ClientPtr c3=CM.registerClient("3","3","3",testaddress1,testType2);
    VehiclePtr v1= VM.registerBicycle("242567",50);
    VehiclePtr v2=  VM.registerCar("819991",500,2000,A);
    VehiclePtr v3=  VM.registerMoped("990142",250,1500);
    VehiclePtr v4= VM.registerBicycle("442568",50);
    RentPtr r1=RM.rentVehicle(1,c1,v1,pt::not_a_date_time);
    RentPtr r2=RM.rentVehicle(2,c3,v2,pt::not_a_date_time);
    RentPtr r3=RM.rentVehicle(3,c1,v3,pt::not_a_date_time);
    RentPtr r4=RM.rentVehicle(4,c2,v4,pt::not_a_date_time);
    vector<RentPtr> rent=RM.findAllRents();
    for (int i=0;i<rent.size();i++){
        cout<<rent[i]->getRentInfo()<<'\n';
    }
    RM.returnVehicle(v2);
    rent=RM.findAllRents();
    for (int i=0;i<rent.size();i++){
        cout<<rent[i]->getRentInfo()<<'\n';
    }
    rent=RM.findAllClientRents(c1);
    for (int i=0;i<rent.size();i++){
        cout<<rent[i]->getRentInfo()<<'\n';
    }
    cout<<RM.findVehicleRent(v4)->getRentInfo()<<'\n';
    CM.unregisterClient("3");
    cout<<c3->isArchive()<<'\n';



    return 0;
}
