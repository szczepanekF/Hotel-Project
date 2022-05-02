#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"

#include "model/Bicycle.h"


struct TestSuiteVehicleRepositoryFixture {
    StorageContainerPtr S=std::make_shared<StorageContainer>();

    VehiclePtr testvehicle1;
    VehiclePtr testvehicle2;

    TestSuiteVehicleRepositoryFixture() {

        testvehicle1 = std::make_shared<Bicycle>("BMW",500);
        testvehicle2 = std::make_shared<Bicycle>("1",1000);

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
    BOOST_AUTO_TEST_CASE(FindByTest) {
        S->get_vehicleRepository().add_vehicle(testvehicle1);
        S->get_vehicleRepository().add_vehicle(testvehicle2);

        BOOST_TEST(S->get_vehicleRepository().findBy([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;}).size() == 1);
        BOOST_TEST(S->get_vehicleRepository().findBy([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;})[0] == testvehicle2);



    }
    BOOST_AUTO_TEST_CASE(FindByPlateNumberTest) {
        S->get_vehicleRepository().add_vehicle(testvehicle1);
        S->get_vehicleRepository().add_vehicle(testvehicle2);

        BOOST_TEST(S->get_vehicleRepository().findByPlateNumber("") == nullptr);
        BOOST_TEST(S->get_vehicleRepository().findByPlateNumber("BMW") == testvehicle1);

    }

    BOOST_AUTO_TEST_CASE(FindAllTest) {
        S->get_vehicleRepository().add_vehicle(testvehicle1);
        S->get_vehicleRepository().add_vehicle(testvehicle2);

        BOOST_TEST(S->get_vehicleRepository().findAll().size() == 4);
        BOOST_TEST(S->get_vehicleRepository().findAll()[0] == S->get_vehicleRepository().get_vehicle(0));
        BOOST_TEST(S->get_vehicleRepository().findAll()[1] == S->get_vehicleRepository().get_vehicle(1));
        BOOST_TEST(S->get_vehicleRepository().findAll()[2] == testvehicle1);
        BOOST_TEST(S->get_vehicleRepository().findAll()[3] == testvehicle2);

    }

BOOST_AUTO_TEST_SUITE_END()
