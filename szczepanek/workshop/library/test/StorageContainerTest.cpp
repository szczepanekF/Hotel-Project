#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"


struct TestSuiteStorageRepositoryFixture {
    StorageContainer x;

    TestSuiteStorageRepositoryFixture() {

    }
    ~TestSuiteStorageRepositoryFixture() {

    }

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteStorageRepository,TestSuiteStorageRepositoryFixture)

    BOOST_AUTO_TEST_CASE(StorageRepositorySizeTest) {

        BOOST_TEST(x.get_clientRepository().size_clientList() == 2);
        //BOOST_TEST(x.get_clientRepository().get_client(0)->getfirstName() == "Filip");
        BOOST_TEST(x.get_vehicleRepository().size_vehicleList() == 2);
        BOOST_TEST(x.get_rentRepository().size_rentList() == 2);
    }


BOOST_AUTO_TEST_SUITE_END()