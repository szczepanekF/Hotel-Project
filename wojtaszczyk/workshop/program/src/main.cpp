
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

void print(boost::uuids::uuid ID){
    cout<<ID<<'\n';
}

int main()
{
    pt::ptime empty = pt::not_a_date_time;

    pt::ptime then1 = pt::ptime(gr::date(2015,5,13),pt::hours(13)+pt::minutes(0)+pt::seconds(0));
    cout<<then1<<endl;
    pt::ptime then2=then1+pt::hours(74);
   // cout<<then2.time_of_day()<<'\n';
    pt::ptime ideal(then1.date(),pt::hours(12));
    unsigned int i=3;
    pt::ptime end;
   // cout<<ideal<<'\n';

        if(ideal>then1){
            end=ideal+pt::hours((i-1)*24);
            cout<<end<<'\n';

        }else{
            end=ideal+pt::hours(i*24);
            cout<<end<<'\n';

        }



//    pt::time_period period(then1,then2);
//    cout<<period.length().hours()<<'\n';
//    pt::ptime ideal = pt::ptime(gr::date(2002,07,15),pt::hours(12)+pt::minutes(00)+pt::seconds(0));
//    cout<<ideal<<'\n';
//    pt::time_period period1(ideal,then1);
//    pt::time_period period2(then1,ideal);
//    cout<<period1.length()<<'\n';
//    cout<<period2.length()<<'\n';

//    cout << empty << endl;
//    pt::ptime now = pt::second_clock::local_time();
//    cout << now << endl;
//    pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25));
//    cout << then << endl;
//    pt::time_period period2(then, now);
//    cout << period2 << endl;
//    cout << period2.length() << endl;
//    cout << period2.length().hours() << endl;
//    cout << period2.length().minutes() << endl;
//    cout << (then>now) << endl;
//    cout << (then<=now) << endl;
//
//    // konwersja ptime na string z użyciem stringstream
//    std::stringstream ss;
//    ss << now;
//    string s = ss.str();
//    cout << s << endl;


//    const std::string testFirstName = "Jon";
//    const std::string testLastName = "Arbuckle";
//    const std::string testPersonalID = "0123456789";
//    AddressPtr testaddress1;
//    AddressPtr testaddress2;
//    ClientTypePtr testType;
//    testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
//    testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
//    testType= std::make_shared<Default>();
//    Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
//    cout<<c.getClientInfo()<<'\n';
//    ClientTypePtr testType2= make_shared<Gold>();
//
//    testType=make_shared<Gold>();
//    cout<<c.getClientInfo()<<'\n';
//    c.setClientType(testType2);
//    testType2=testType;
//    cout<<testType2->getTypeInfo()<<'\n';
//    cout<<c.getClientInfo()<<'\n';

//    const std::string testplateNumber= "Jon";
//    const unsigned int  testbasePrice = 20;
//    const unsigned int engine1=1000;
//
//    VehiclePtr testVehicle;
//    testVehicle= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,A);
//    cout<<testVehicle->getInfo();
//    boost::uuids::random_generator gen;
//    boost::uuids::uuid ID = gen();
//    for(int i=0;i<5;i++){
//        print(ID);
//        ID=gen();
//    }
//    RentRepository S;
//
//    const std::string testFirstName = "Jon";
//    const std::string testLastName = "Arbuckle";
//    const std::string testPersonalID = "0123456789";
//    AddressPtr testaddress1;
//    boost::uuids::uuid ID={11};
//    const std::string testplateNumber= "Jon";
//    const unsigned int  testbasePrice = 50;
//    ClientPtr testClient;
//    VehiclePtr testVehicle;
//    ClientTypePtr testType;
//    testType= std::make_shared<Default>();
//    testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
//    testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress1,testType);
//    testVehicle= std::make_shared<Bicycle>(testplateNumber,testbasePrice);
//    RentPtr ptr= make_shared<Rent>(ID,testClient,testVehicle,pt::not_a_date_time);
//    S.add(ptr);
//    boost::uuids::uuid ID2={11};
//    int i=1;
//    while(S.findBy([ID](const RentPtr &X)->bool{return X->getId()==ID;}).size()!=0){
//        ID=boost::uuids::random_generator()();
//        cout<<i++<<'\n';
//    }
//    RentPtr ptr2= make_shared<Rent>(ID,testClient,testVehicle,pt::not_a_date_time);
//    S.add(ptr2);
//    cout<<S.get(0)->getInfo()<<'\n';
//    cout<<S.get(1)->getInfo()<<'\n';

    return 0;
}
