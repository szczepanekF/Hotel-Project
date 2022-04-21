#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "model/Default.h"

struct TestSuiteClientRepositoryFixture {
    StorageContainerPtr S=std::make_shared<StorageContainer>() ;
    AddressPtr testaddress1;
    ClientPtr testclient1;
    ClientPtr testclient2;
    ClientTypePtr pt1;

    TestSuiteClientRepositoryFixture() {
//        S = std::make_shared<StorageContainer>();
        pt1 = std::make_shared<Default>();
        testaddress1 = std::make_shared<Address>("nowy","adres","123");
        testclient1 = std::make_shared<Client>("klient","testowy","444",testaddress1,pt1);
        testclient2 = std::make_shared<Client>("klient2","testpid","444",testaddress1,pt1);

   }
    ~TestSuiteClientRepositoryFixture() {
//        delete testaddress1;
//        delete S;
    }

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository,TestSuiteClientRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {
        BOOST_TEST(S->get_clientRepository().size_clientList() == 2);
    }
    BOOST_AUTO_TEST_CASE(GetTest) {
        BOOST_TEST(S->get_clientRepository().get_client(100) == nullptr);
        S->get_clientRepository().add_client(testclient1);
        BOOST_TEST(S->get_clientRepository().get_client(2) == testclient1);
    }

    BOOST_AUTO_TEST_CASE(AddAndRemoveTest) {
        S->get_clientRepository().add_client(nullptr);
        BOOST_TEST(S->get_clientRepository().size_clientList() == 2);
        S->get_clientRepository().add_client(testclient1);
        BOOST_TEST(S->get_clientRepository().size_clientList() == 3);
        S->get_clientRepository().remove_client(nullptr);
        BOOST_TEST(S->get_clientRepository().size_clientList() == 3);
        S->get_clientRepository().remove_client(testclient1);
        BOOST_TEST(S->get_clientRepository().size_clientList() == 2);
    }
    BOOST_AUTO_TEST_CASE(FindByPersonalIdTest) {
        S->get_clientRepository().add_client(testclient1);
        BOOST_TEST(S->get_clientRepository().findByPersonalId("444") == testclient1);
        BOOST_TEST(S->get_clientRepository().findByPersonalId("") == nullptr);
    }

BOOST_AUTO_TEST_SUITE_END()
