#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "model/Bicycle.h"
#include "model/Default.h"


struct TestSuiteRentRepositoryFixture {
    StorageContainerPtr S= std::make_shared<StorageContainer>();
    AddressPtr testaddress1;
    ClientPtr testclient1;
    VehiclePtr testvehicle1;
    ClientTypePtr pt1;
    const unsigned int test_id =1;
    RentPtr testrent1;


    TestSuiteRentRepositoryFixture() {
        pt1 =std::make_shared<Default>();

        testaddress1 = std::make_shared<Address>("nowy","adres","123");
        testclient1 = std::make_shared<Client>("klient","testowy","444",testaddress1,pt1);
        testvehicle1 = std::make_shared<Bicycle>("testowy",444);
        testrent1 = std::make_shared<Rent>(test_id,testclient1,testvehicle1,pt::not_a_date_time);
    }
    ~TestSuiteRentRepositoryFixture() {
//        delete testaddress1;
//        delete testclient1;
//        delete testvehicle1;
//        delete S;
    }
};



BOOST_FIXTURE_TEST_SUITE(TestSuiteRentRepository,TestSuiteRentRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {
        BOOST_TEST(S->get_rentRepository().size_rentList() == 2);
    }
    BOOST_AUTO_TEST_CASE(GetTest) {
        BOOST_TEST(S->get_rentRepository().get_rent(1000) == nullptr);
        S->get_rentRepository().add_rent(testrent1);
        BOOST_TEST(S->get_rentRepository().get_rent(2) == testrent1);
    }

    BOOST_AUTO_TEST_CASE(AddAndRemoveTest) {
        S->get_rentRepository().add_rent(nullptr);
        BOOST_TEST(S->get_rentRepository().size_rentList() == 2);
        S->get_rentRepository().add_rent(testrent1);
        BOOST_TEST(S->get_rentRepository().size_rentList() == 3);
        S->get_rentRepository().remove_rent(nullptr);
        BOOST_TEST(S->get_rentRepository().size_rentList() == 3);
        S->get_rentRepository().remove_rent(testrent1);
        BOOST_TEST(S->get_rentRepository().size_rentList() == 2);
    }





BOOST_AUTO_TEST_SUITE_END()
