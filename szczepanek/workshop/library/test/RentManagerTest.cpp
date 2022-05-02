#include <boost/test/unit_test.hpp>
#include "managers/RentManager.h"
#include "model/Bicycle.h"
#include "model/Moped.h"
#include "model/Car.h"

#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"

namespace pt = boost::posix_time;

struct TestSuiteRentManagerFixture{
    const unsigned int testid1 = 1;
    const unsigned int testid2 = 2;
    const unsigned int testid3 = 3;

    const std::string testPID1 = "1";
    const std::string testPID2 = "2";

    std::string testplates1 = "car";
    const unsigned int testprice1 = 5000;
    std::string testplates3 = "bike";
    const unsigned int testprice3 = 10;
    std::string testplates2 = "moped";
    const unsigned int testprice2 = 100;
    const unsigned int testEngineDisplacement2 = 500;
    const unsigned int testEngineDisplacement1 = 1;
    SegmentType testsegment = A;


    AddressPtr testaddress1;
    ClientPtr testclient1;
    ClientPtr testclient2;
    VehiclePtr testvehicle1;
    VehiclePtr testvehicle2;
    VehiclePtr testvehicle3;
    ClientTypePtr pt1;
    ClientTypePtr pt2;
    ClientTypePtr pt3;
//    ClientTypePtr pt4;
//    ClientTypePtr pt5;
//    ClientTypePtr pt6;
    RentManagerPtr RM = std::make_shared<RentManager>();

    TestSuiteRentManagerFixture(){
        pt1 = std::make_shared<Default>();
        pt2 = std::make_shared<Bronze>();
        pt3 = std::make_shared<Silver>();
//        pt4 = std::make_shared<Gold>();
//        pt5 = std::make_shared<Platinum>();
//        pt6 = std::make_shared<Diamond>();
        testaddress1=std::make_shared<Address>("London", "Accacia Avenue", "22");
        testclient1 = std::make_shared<Client>("Jon","Arbuckle",testPID1,testaddress1,pt2);
        testclient2 = std::make_shared<Client>("Filip","Szczepanek",testPID2,testaddress1,pt1);

        testvehicle1 = std::make_shared<Bicycle>(testplates3,testprice3);
        testvehicle2 = std::make_shared<Moped>(testplates2,testprice2,testEngineDisplacement2);
        testvehicle3 = std::make_shared<Car>(testplates3,testprice3,testEngineDisplacement1,testsegment);

    }
    ~TestSuiteRentManagerFixture(){

    }
};
//bool testrentpredicate1(const RentPtr ptr)
//{
//    return ptr->get_beginTime()==pt::second_clock::local_time()+pt::minutes(50);
//}

BOOST_FIXTURE_TEST_SUITE(TestSuiteRentManager, TestSuiteRentManagerFixture)

    BOOST_AUTO_TEST_CASE(getAllClientRentsTest) {
        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::not_a_date_time);
        RM->rentVehicle(testid2,testclient1,testvehicle2,pt::not_a_date_time);
        RM->rentVehicle(testid2,testclient2,testvehicle2,pt::not_a_date_time);

        BOOST_TEST(RM->getAllClientRents(testclient2).size()==0);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);

        BOOST_TEST(RM->getAllClientRents(testclient1).size()==2);
        BOOST_TEST(RM->getAllClientRents(testclient2).size()==1);


        BOOST_TEST(RM->getAllClientRents(testclient1)[0]==RM->getVehicleRent(testvehicle1));
        BOOST_TEST(RM->getAllClientRents(testclient1)[1]==RM->getVehicleRent(testvehicle2));
        BOOST_TEST(RM->getAllClientRents(testclient2)[0]==RM->getVehicleRent(testvehicle3));

    }
BOOST_AUTO_TEST_CASE(getVehicleRentTest) {
        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::not_a_date_time);

        BOOST_TEST(RM->getVehicleRent(testvehicle2)==nullptr);


}
BOOST_AUTO_TEST_CASE(findRentsTest) {
        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::second_clock::local_time()+pt::minutes(50));
        RM->rentVehicle(testid2,testclient1,testvehicle2,pt::not_a_date_time);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);
        BOOST_TEST_REQUIRE(RM->findRents([](const RentPtr ptr){return ptr->get_beginTime()==pt::second_clock::local_time()+pt::minutes(50);}).size()==1);
        BOOST_TEST(RM->findRents([](const RentPtr ptr){return ptr->get_beginTime()==pt::second_clock::local_time()+pt::minutes(50);})[0] == RM->getVehicleRent(testvehicle1));

        RM->returnVehicle(testvehicle1);
        BOOST_TEST(RM->findRents([](const RentPtr ptr){return ptr->get_beginTime()==pt::second_clock::local_time()+pt::minutes(50);}).size()==0);


    }
BOOST_AUTO_TEST_CASE(findAllRentsTest) {
        BOOST_TEST(RM->findAllRents().size()==0);
        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::second_clock::local_time()+pt::minutes(50));
        RM->rentVehicle(testid2,testclient1,testvehicle2,pt::not_a_date_time);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);

        BOOST_TEST(RM->findAllRents().size()==3);
        BOOST_TEST(RM->findAllRents()[0]==RM->getVehicleRent(testvehicle1));
        BOOST_TEST(RM->findAllRents()[1]==RM->getVehicleRent(testvehicle2));
        BOOST_TEST(RM->findAllRents()[2]==RM->getVehicleRent(testvehicle3));


}

    BOOST_AUTO_TEST_CASE(rentvehicleTest) {

        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::second_clock::local_time()+pt::minutes(50));
        RM->rentVehicle(testid2,testclient1,testvehicle2,pt::not_a_date_time);
        RM->rentVehicle(testid3,testclient1,testvehicle3,pt::not_a_date_time);
        BOOST_TEST(RM->getAllClientRents(testclient1).size()==2);
        testclient1->setArchive(true);
        testclient1->set_clientType(pt3);
        RM->rentVehicle(testid3,testclient1,testvehicle3,pt::not_a_date_time);
        BOOST_TEST(RM->getAllClientRents(testclient1).size()==2);
        RM->rentVehicle(testid3,testclient1,nullptr,pt::not_a_date_time);
        BOOST_TEST(RM->getAllClientRents(testclient1).size()==2);

        BOOST_TEST(RM->getVehicleRent(testvehicle3)==nullptr);
        testvehicle3->setArchive(true);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);
        BOOST_TEST(RM->getVehicleRent(testvehicle3)==nullptr);
        testvehicle3->setArchive(false);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);
        BOOST_TEST(RM->getVehicleRent(testvehicle3)!=nullptr);

    }

    BOOST_AUTO_TEST_CASE(returnVehicleTest) {
        BOOST_TEST(RM->findAllRents().size()==0);
        RM->rentVehicle(testid1,testclient1,testvehicle1,pt::second_clock::local_time()+pt::minutes(50));
        RM->rentVehicle(testid2,testclient1,testvehicle2,pt::not_a_date_time);
        RM->rentVehicle(testid3,testclient2,testvehicle3,pt::not_a_date_time);
        BOOST_TEST(RM->findAllRents().size()==3);
        RM->returnVehicle(nullptr);
        BOOST_TEST(RM->findAllRents().size()==3);
        RentPtr rent= RM->getVehicleRent(testvehicle3);
        RM->returnVehicle(testvehicle3);
        BOOST_TEST(RM->findAllRents().size()==2);

        BOOST_TEST(rent->get_endTime()!=pt::not_a_date_time);
        BOOST_TEST(rent->get_endTime()==pt::second_clock::local_time());
    }

    BOOST_AUTO_TEST_CASE(getClientBalanceTest) {

        RM->rentVehicle(testid1,testclient1,testvehicle3,pt::second_clock::local_time()-pt::minutes(50));
        RM->rentVehicle(testid1,testclient1,testvehicle2,pt::second_clock::local_time()-pt::minutes(50));
        BOOST_TEST(RM->checkClientRentBalance(testclient1)==0);
        BOOST_TEST(RM->checkClientRentBalance(nullptr)==0);

        RM->returnVehicle(testvehicle3);
        BOOST_TEST(RM->checkClientRentBalance(testclient1)==7);
        RM->returnVehicle(testvehicle2);
        BOOST_TEST(RM->checkClientRentBalance(testclient1)==104);



    }


    BOOST_AUTO_TEST_CASE(changeClientTypetoDefaultTest) {

        RM->rentVehicle(testid1,testclient1,testvehicle3,pt::second_clock::local_time()-pt::minutes(50));
        RM->returnVehicle(testvehicle3);
        BOOST_TEST(testclient1->getMaxVehicles()==2);

        RM->changeClientType(testclient1);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)<100);

        BOOST_TEST(testclient1->getMaxVehicles()==1);
    }
    BOOST_AUTO_TEST_CASE(changeClientTypetoBronzeTest) {

        RM->rentVehicle(testid1,testclient2,testvehicle2,pt::second_clock::local_time()-pt::hours(23));
        RM->returnVehicle(testvehicle2);

        BOOST_TEST(testclient2->getMaxVehicles()==1);

        RM->changeClientType(testclient2);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)>=100);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)<200);

        BOOST_TEST(testclient2->getMaxVehicles()==2);
    }
    BOOST_AUTO_TEST_CASE(changeClientTypetoSilverTest) {

        RM->rentVehicle(testid1,testclient2,testvehicle2,pt::second_clock::local_time()-pt::hours(24));
        RM->returnVehicle(testvehicle2);

        BOOST_TEST(testclient2->getMaxVehicles()==1);

        RM->changeClientType(testclient2);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)>=200);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)<400);

        BOOST_TEST(testclient2->getMaxVehicles()==3);
    }
    BOOST_AUTO_TEST_CASE(changeClientTypetoGoldTest) {

        RM->rentVehicle(testid1,testclient2,testvehicle2,pt::second_clock::local_time()-pt::hours(72));
        RM->returnVehicle(testvehicle2);

        BOOST_TEST(testclient2->getMaxVehicles()==1);

        RM->changeClientType(testclient2);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)>=400);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)<800);

        BOOST_TEST(testclient2->getMaxVehicles()==4);
    }
    BOOST_AUTO_TEST_CASE(changeClientTypetoPlatinumTest) {

        RM->rentVehicle(testid1,testclient2,testvehicle2,pt::second_clock::local_time()-pt::hours(168));
        RM->returnVehicle(testvehicle2);



        BOOST_TEST(testclient2->getMaxVehicles()==1);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)>=800);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)<1600);
        RM->changeClientType(testclient2);

        BOOST_TEST(testclient2->getMaxVehicles()==5);
    }
    BOOST_AUTO_TEST_CASE(changeClientTypetoDiamondTest) {

        RM->rentVehicle(testid1,testclient2,testvehicle2,pt::second_clock::local_time()-pt::hours(2400));
        RM->returnVehicle(testvehicle2);
        BOOST_TEST(RM->checkClientRentBalance(testclient2)>=1600);
        BOOST_TEST(testclient2->getMaxVehicles()==1);

        RM->changeClientType(testclient2);

        BOOST_TEST(testclient2->getMaxVehicles()==10);
    }


    BOOST_AUTO_TEST_SUITE_END()


