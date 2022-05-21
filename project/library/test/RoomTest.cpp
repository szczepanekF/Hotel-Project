#include <boost/test/unit_test.hpp>
#include "model/Room.h"
#include "model/RoomWithTerrace.h"
#include "model/RoomWithoutTerrace.h"
using namespace std;
namespace btt = boost::test_tools;
struct TestSuiteRoomFixture{
    int num1=1;
    double baseprice1=100;
    double baseprice2=150;
    int bedcount1=1;
    int bedcount2=2;
    int bedcount3=-1;
    double terrace1=50;
    double terrace2=150;
    double terrace3=350;
//    double terrace4=550;


    TestSuiteRoomFixture(){
    }
    ~TestSuiteRoomFixture(){

    }
};
BOOST_FIXTURE_TEST_SUITE(RoomTestSuite,TestSuiteRoomFixture)

BOOST_AUTO_TEST_CASE(RoomConstructorTest)
{
    RoomWithTerrace room1(num1,baseprice1,bedcount1,A,terrace1);
    BOOST_TEST(room1.getRoomNumber() == num1);
    BOOST_TEST(room1.getBasePricePerNight() == baseprice1);
    BOOST_TEST(room1.getBedCount() == bedcount1);
    BOOST_TEST(room1.getExtraBonus() == A);
    BOOST_TEST(room1.getTerraceSurface() == terrace1);

    RoomWithoutTerrace room2(num1,baseprice1,bedcount1,A);
    BOOST_TEST(room2.getRoomNumber() == num1);
    BOOST_TEST(room2.getBasePricePerNight() == baseprice1);
    BOOST_TEST(room2.getBedCount() == bedcount1);
    BOOST_TEST(room2.getExtraBonus() == A);
}
BOOST_AUTO_TEST_CASE(RoomGetPricePerNightTest)
{
    RoomWithoutTerrace room(num1,baseprice1,bedcount1,A);
    BOOST_TEST(room.getPricePerNight() == baseprice1);
    room.setExtraBonus(B);
    BOOST_TEST(room.getPricePerNight() == baseprice1+100);
    room.setExtraBonus(C);
    BOOST_TEST(room.getPricePerNight() == baseprice1+250);
    room.setExtraBonus(D);
    BOOST_TEST(room.getPricePerNight() == baseprice1+500);
    room.setExtraBonus(E);
    BOOST_TEST(room.getPricePerNight() == baseprice1+1000);

}
BOOST_AUTO_TEST_CASE(RoomSetBedCountTest)
{
    RoomWithoutTerrace room(num1,baseprice1,bedcount1,A);
    room.setBedCount(bedcount2);
    BOOST_TEST(room.getBedCount() == bedcount2);
    room.setBedCount(bedcount3);
    BOOST_TEST(room.getBedCount() == bedcount2);
}
BOOST_AUTO_TEST_CASE(RoomWithTerraceFinalPriceTest)
{
    RoomWithTerrace room1(num1,baseprice1,bedcount1,A,terrace1);
    BOOST_TEST(room1.getFinalPricePerNight() == baseprice1);
    RoomWithTerrace room2(num1,baseprice1,bedcount1,A,terrace2);
    BOOST_TEST(room2.getFinalPricePerNight() == baseprice1*1.2);
    RoomWithTerrace room3(num1,baseprice1,bedcount1,A,terrace3);
    BOOST_TEST(room3.getFinalPricePerNight() == baseprice1*1.5);
}

BOOST_AUTO_TEST_CASE(RoomWithoutTerraceFinalPriceTest)
{
    RoomWithoutTerrace room(num1,baseprice1,bedcount1,A);
    BOOST_TEST(room.getFinalPricePerNight() == baseprice1);
}





BOOST_AUTO_TEST_SUITE_END()
