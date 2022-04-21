#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"

#include "model/Bicycle.h"
struct TestSuiteVehicleRepositoryFixture {
    StorageContainerPtr S=std::make_shared<StorageContainer>();

    VehiclePtr testvehicle1;

    TestSuiteVehicleRepositoryFixture() {

        testvehicle1 = std::make_shared<Bicycle>("BMW",500);
    }
    ~TestSuiteVehicleRepositoryFixture() {
//        delete S;
    }

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleRepository,TestSuiteVehicleRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {
        BOOST_TEST(S->get_vehicleRepository().size_vehicleList() == 2);
    }
    BOOST_AUTO_TEST_CASE(GetTest) {
        BOOST_TEST(S->get_vehicleRepository().get_vehicle(1000) == nullptr);
        S->get_vehicleRepository().add_vehicle(testvehicle1);
        BOOST_TEST(S->get_vehicleRepository().get_vehicle(2) == testvehicle1);
    }

    BOOST_AUTO_TEST_CASE(AddAndRemoveTest) {
        S->get_vehicleRepository().add_vehicle(nullptr);
        BOOST_TEST(S->get_vehicleRepository().size_vehicleList() == 2);
        S->get_vehicleRepository().add_vehicle(testvehicle1);
        BOOST_TEST(S->get_vehicleRepository().size_vehicleList() == 3);
        S->get_vehicleRepository().remove_vehicle(nullptr);
        BOOST_TEST(S->get_vehicleRepository().size_vehicleList() == 3);
        S->get_vehicleRepository().remove_vehicle(testvehicle1);
        BOOST_TEST(S->get_vehicleRepository().size_vehicleList() == 2);
    }

BOOST_AUTO_TEST_SUITE_END()
