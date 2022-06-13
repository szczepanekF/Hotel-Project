#include <boost/test/unit_test.hpp>
#include "model/Room.h"
#include "model/RoomWithTerrace.h"
#include "model/RoomWithoutTerrace.h"
#include "exceptions/RoomError.h"

using namespace std;

namespace btt = boost::test_tools;

struct TestSuiteRoomFixture{
    int num1=1;
    double baseprice1=100;

    int bedcount1=1;
    int bedcount2=2;
    int bedcount3=-1;
    double terrace1=4;
    double terrace2=9;
    double terrace3=11;



    TestSuiteRoomFixture()= default;
    ~TestSuiteRoomFixture()= default;
};
BOOST_FIXTURE_TEST_SUITE(RoomTestSuite,TestSuiteRoomFixture)

BOOST_AUTO_TEST_CASE(RoomConstructorTest)
{
    RoomWithTerrace room1(num1,baseprice1,bedcount1,terrace1);
    BOOST_TEST(room1.getId() == num1);
    BOOST_TEST(room1.getBasePricePerNight() == baseprice1);
    BOOST_TEST(room1.getBedCount() == bedcount1);
    BOOST_TEST(room1.getTerraceSurface() == terrace1);

    RoomWithoutTerrace room2(num1,baseprice1,bedcount1);
    BOOST_TEST(room2.getId() == num1);
    BOOST_TEST(room2.getBasePricePerNight() == baseprice1);
    BOOST_TEST(room2.getBedCount() == bedcount1);

}
    BOOST_AUTO_TEST_CASE(RoomConstructorTestExceptions)
    {

        BOOST_REQUIRE_THROW(RoomWithoutTerrace room2(0,baseprice1,bedcount1),RoomError);
        BOOST_CHECK_EXCEPTION(RoomWithoutTerrace room2(0,baseprice1,bedcount1),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR Wrong room number";});
        BOOST_REQUIRE_THROW(RoomWithoutTerrace room2(num1,0,bedcount1),RoomError);
        BOOST_CHECK_EXCEPTION(RoomWithoutTerrace room2(num1,0,bedcount1),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR Wrong base price";});
        BOOST_REQUIRE_THROW(RoomWithoutTerrace room2(num1,baseprice1,0),RoomError);
        BOOST_CHECK_EXCEPTION(RoomWithoutTerrace room2(num1,baseprice1,0),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR Wrong bed count";});
        BOOST_REQUIRE_THROW(RoomWithTerrace room2(num1,baseprice1,bedcount1,0),RoomError);
        BOOST_CHECK_EXCEPTION(RoomWithTerrace room2(num1,baseprice1,bedcount1,0),RoomError,
                              [] (const RoomError &e){return e.information()=="Error Wrong terrace surface";});
    }


BOOST_AUTO_TEST_CASE(RoomSetBedCountTest)
{
    RoomWithoutTerrace room(num1,baseprice1,bedcount1);
    room.setBedCount(bedcount2);
    BOOST_TEST(room.getBedCount() == bedcount2);
    BOOST_REQUIRE_THROW(room.setBedCount(bedcount3),RoomError);
    BOOST_CHECK_EXCEPTION(room.setBedCount(bedcount3),RoomError,
                          [] (const RoomError &e){return e.information()=="ERROR Wrong bed count";});
    BOOST_TEST(room.getBedCount() == bedcount2);
}
BOOST_AUTO_TEST_CASE(RoomWithTerraceFinalPriceTest)
{
    RoomWithTerrace room1(num1,baseprice1,bedcount1,terrace1);
    BOOST_TEST(room1.getFinalPricePerNight() == baseprice1);
    RoomWithTerrace room2(num1,baseprice1,bedcount1,terrace2);
    BOOST_TEST(room2.getFinalPricePerNight() == baseprice1*1.2);
    RoomWithTerrace room3(num1,baseprice1,bedcount1,terrace3);
    BOOST_TEST(room3.getFinalPricePerNight() == baseprice1*1.5);
}

BOOST_AUTO_TEST_CASE(RoomWithoutTerraceFinalPriceTest)
{
    RoomWithoutTerrace room(num1,baseprice1,bedcount1);
    BOOST_TEST(room.getFinalPricePerNight() == baseprice1);
}





BOOST_AUTO_TEST_SUITE_END()
