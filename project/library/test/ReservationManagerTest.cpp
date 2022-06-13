

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Standard.h"
#include "model/ShortTerm.h"
#include "model/LongTerm.h"
#include "model/RoomWithTerrace.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/ReservationRepository.h"
#include "managers/ReservationManager.h"
#include "exceptions/ReservationError.h"

namespace gr = boost::gregorian;

struct ReservationManagerFixture {
    ReservationRepositoryPtr currentRR;
    ReservationRepositoryPtr archiveRR;

    ud::uuid testId1 ={1};
    ud::uuid testId2 ={2};
    ud::uuid testId3 ={3};
    unsigned int testGuestCount = 3;
    unsigned int testReservationDays1 =2;
    unsigned int testReservationDays2 =4;
    unsigned int testReservationDays3 =8;
    pt::ptime testBeginTime = pt::second_clock::local_time();
    ClientTypePtr testType;
    ClientTypePtr testType2;
    ClientTypePtr testType3;
    ClientPtr testClient;
    ClientPtr testClient2;
    ClientPtr testClient3;

    RoomPtr testRoom;
    RoomPtr testRoom2;
    RoomPtr testRoom3;

    ReservationPtr testReservation;
    ReservationPtr testReservation2;
    ReservationPtr testReservation3;

    std::vector<ReservationPtr> testReservations;
    ReservationPtr nullReservation=nullptr;

    ReservationManagerFixture() {
        currentRR = std::make_shared<ReservationRepository>();
        archiveRR = std::make_shared<ReservationRepository>();
        testType2=std::make_shared<Standard>();
        testType=std::make_shared<ShortTerm>();
        testType3=std::make_shared<LongTerm>();
        testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
        testClient2 = std::make_shared<Client>("Stanislaw","Kowalski","242567",testType2);
        testClient3 = std::make_shared<Client>("Ktos","Ziemowit","444091",testType3);
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,3);
        testRoom2 = std::make_shared<RoomWithTerrace>(2,500,3,200);
        testRoom3 = std::make_shared<RoomWithoutTerrace>(3,500,3);


    }

    ~ReservationManagerFixture() = default;

};
BOOST_FIXTURE_TEST_SUITE(TestSuiteReservationManager,ReservationManagerFixture)

    BOOST_AUTO_TEST_CASE(StartAndFindRoomReservationTest) {
        ReservationManager RM(currentRR,archiveRR);
        BOOST_REQUIRE(currentRR->size() == 0);
        testClient->setBill(100);
        testClient2->setBill(2000);
        testClient3->setBill(3000);
        testReservation = RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime, testReservationDays1,
                                              A);
        testReservation2 = RM.startReservation(testClient2, testRoom2, testGuestCount, testBeginTime,
                                               testReservationDays2, B);
        testReservation3 = RM.startReservation(testClient3, testRoom3, testGuestCount, testBeginTime,
                                               testReservationDays3, C);
        BOOST_TEST(testReservation->getId()!=testReservation2->getId());
        BOOST_TEST(testReservation2->getId()!=testReservation3->getId());
        BOOST_TEST(testReservation->getId()!=testReservation3->getId());
        BOOST_REQUIRE(currentRR->size() == 3);
        BOOST_REQUIRE(archiveRR->size() == 0);
        BOOST_TEST(RM.findRoomReservation(testRoom) == testReservation);
        BOOST_TEST(RM.findRoomReservation(testRoom2) == testReservation2);
        BOOST_TEST(RM.findRoomReservation(testRoom3) == testReservation3);
        BOOST_TEST(testReservation->getTotalReservationCost()==100+testReservation->getPricePerNight()*testReservation->getReservationDays());
        BOOST_TEST(testReservation2->getTotalReservationCost()==2000+testReservation2->getPricePerNight()*testReservation2->getReservationDays());
        BOOST_TEST(testReservation3->getTotalReservationCost()==3000+testReservation3->getPricePerNight()*testReservation3->getReservationDays());
        BOOST_TEST(testClient->getBill()==0);
        BOOST_TEST(testClient2->getBill()==0);
        BOOST_TEST(testClient3->getBill()==0);
        RM.endReservation(testReservation3->getId());
        testClient3->setBill(-3000);
        ReservationPtr res=RM.startReservation(testClient3, testRoom3, testGuestCount, testBeginTime,
                            1, C);
        BOOST_TEST(res->getTotalReservationCost()==0);
        BOOST_TEST(testClient3->getBill()==0);




    }
    BOOST_AUTO_TEST_CASE(StartAndFindRoomReservationErrorTest) {
        ReservationManager RM(currentRR,archiveRR);
        testReservation = RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime, testReservationDays1,
                                              A);
        testReservation2 = RM.startReservation(testClient2, testRoom2, testGuestCount, testBeginTime,
                                               testReservationDays2, B);
        std::string information = testReservation->getInfo();
        BOOST_REQUIRE_THROW(RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime, testReservationDays1,
                                              A), ReservationError);
        BOOST_CHECK_EXCEPTION(RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime,
                                                  testReservationDays1, A), ReservationError,
                              [information] (const ReservationError &e){return e.information()=="ERROR already exists: "+information;});
        BOOST_TEST(currentRR->size()==2);

        BOOST_REQUIRE_THROW(nullReservation=RM.findRoomReservation(testRoom3),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.findRoomReservation(testRoom3),ReservationError,
                              [] (const HotelError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(nullReservation==nullptr);

        BOOST_CHECK_THROW(nullReservation=RM.startReservation(testClient, testRoom3, 3, testBeginTime - pt::hours(30), 1, B), ReservationError);
        BOOST_CHECK_EXCEPTION(RM.startReservation(testClient, testRoom3, 3, testBeginTime - pt::hours(30), 1, B), ReservationError,
                              [](const HotelError &e){return e.information()=="Error Wrong begin time";});
        BOOST_TEST(nullReservation==nullptr);

        BOOST_CHECK_THROW(nullReservation=RM.startReservation(testClient, testRoom3, 4, testBeginTime, 1, B), ReservationError);
        BOOST_CHECK_EXCEPTION(RM.startReservation(testClient, testRoom3, 4, testBeginTime, 1, B), ReservationError,
                              [](const HotelError &e){return e.information()=="Error Too many guests";});
        BOOST_TEST(nullReservation==nullptr);

        BOOST_CHECK_THROW(nullReservation=RM.startReservation(testClient, testRoom3, 3, testBeginTime, 8, B), ReservationError);
        BOOST_CHECK_EXCEPTION(RM.startReservation(testClient, testRoom3, 3, testBeginTime, 8, B), ReservationError,
                              [](const HotelError &e){return e.information()=="Error Wrong reservation days";});
        BOOST_TEST(nullReservation==nullptr);
    }
    BOOST_AUTO_TEST_CASE(EndTest) {
        ReservationManager RM(currentRR,archiveRR);

        testReservation = RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime, testReservationDays1,
                                              A);
        testReservation2 = RM.startReservation(testClient2, testRoom2, testGuestCount, testBeginTime,
                                               testReservationDays2, B);
        testReservation3 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                         testReservationDays3, C);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation3);

        BOOST_TEST(currentRR->size() == 3);
        BOOST_TEST(archiveRR->size() == 0);
        RM.endReservation(testId3);
        BOOST_TEST(currentRR->size() == 2);
        BOOST_TEST(archiveRR->size() == 1);
        testClient3->setBill(300);

        archiveRR->remove(testReservation3);
        ReservationPtr res1= std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                         6, C);
        currentRR->add(res1);
        RM.endReservation(testId3);
        ReservationPtr res2 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                         1, C);
        res2->setTotalReservationCost(res2->calculateBaseReservationCost());
        currentRR->add(res2);
        BOOST_TEST(RM.calculateDiscount(testClient3)==0);

        RM.endReservation(testId3);
        BOOST_TEST(res2->getClient()->getBill()==300);
        BOOST_TEST(RM.calculateDiscount(testClient3)==0.02);

        ReservationPtr res3 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                            13, C);
        res3->setTotalReservationCost(res3->calculateBaseReservationCost());
        currentRR->add(res3);
        RM.endReservation(testId3);

        BOOST_TEST(res3->getClient()->getBill()==300-0.02*res3->getTotalReservationCost());
        ReservationPtr res4 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                            1, C);
        res4->setTotalReservationCost(res4->calculateBaseReservationCost());
        currentRR->add(res4);
        RM.endReservation(testId3);
        BOOST_TEST(RM.calculateDiscount(testClient3)==0.05);
        double help = 300 - 0.02*(res3->getTotalReservationCost()+res4->getTotalReservationCost());
        BOOST_TEST(res4->getClient()->getBill()==help);
        ReservationPtr res5 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                            38, C);
        res5->setTotalReservationCost(res5->calculateBaseReservationCost());
        currentRR->add(res5);
        RM.endReservation(testId3);

        BOOST_TEST(res5->getClient()->getBill()==help-0.05*res5->getTotalReservationCost());


        ReservationPtr res6 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                            1, C);
        res6->setTotalReservationCost(res5->calculateBaseReservationCost());
        double help2 =help - 0.05*(res5->getTotalReservationCost()+res6->getTotalReservationCost());
        currentRR->add(res6);
        RM.endReservation(testId3);
        BOOST_TEST(RM.calculateDiscount(testClient3)==0.07);
        BOOST_TEST(res6->getClient()->getBill()==help2);
        ReservationPtr res7 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                                            1, C);
        res7->setTotalReservationCost(res5->calculateBaseReservationCost());

        currentRR->add(res7);
        RM.endReservation(testId3);
        BOOST_TEST(res7->getClient()->getBill()==help2-0.07*res7->getTotalReservationCost());
    }
    BOOST_AUTO_TEST_CASE(EndErrorTest) {
        ReservationManager RM(currentRR,archiveRR);
        testReservation3 = RM.startReservation(testClient3, testRoom3, testGuestCount, testBeginTime,
                                               testReservationDays3, C);
        BOOST_CHECK_THROW(RM.endReservation(testId2),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.endReservation(testId2),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Object";});

    }

    BOOST_AUTO_TEST_CASE(FindTest){
        ReservationManager RM(currentRR,archiveRR);
        BOOST_TEST(currentRR->size() == 0);
        testReservation = RM.startReservation(testClient, testRoom, testGuestCount, testBeginTime, testReservationDays1,
                                              A);
        testReservation2 = RM.startReservation(testClient, testRoom2, testGuestCount, testBeginTime,
                                               testReservationDays1, C);
        testReservation3 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                               testReservationDays3, C);
        currentRR->add(testReservation3);

        BOOST_TEST(RM.findAllReservations().size()==3);
        BOOST_TEST(RM.findAllReservations()[0]==testReservation);
        BOOST_TEST(RM.findAllReservations()[1]==testReservation2);
        BOOST_TEST(RM.findAllReservations()[2]==testReservation3);
        BOOST_TEST(RM.findReservations([](const ReservationPtr &ptr){return ptr->getExtraBonus()==C;}).size()==2);
        BOOST_TEST(RM.findReservations([](const ReservationPtr &ptr){return ptr->getExtraBonus()==C;})[0]==testReservation2);
        BOOST_TEST(RM.findReservations([](const ReservationPtr &ptr){return ptr->getExtraBonus()==C;})[1]==testReservation3);
        BOOST_TEST(RM.findClientReservations(testClient).size()==2);
        BOOST_TEST(RM.findClientReservations(testClient)[0]==testReservation);
        BOOST_TEST(RM.findClientReservations(testClient)[1]==testReservation2);
        RM.endReservation(testId3);
        BOOST_TEST(RM.findAllReservations().size()==2);
        BOOST_TEST(RM.findReservations([](const ReservationPtr &ptr){return ptr->getExtraBonus()==C;}).size()==1);
        BOOST_TEST(RM.findClientReservations(testClient).size()==2);
    }
    BOOST_AUTO_TEST_CASE(ErrorFindTest){
        ReservationManager RM(currentRR,archiveRR);

        testReservation = std::make_shared<Reservation>(testClient, testRoom, testGuestCount,testId1, testBeginTime, testReservationDays1,
                                              A);
        testReservation2 = std::make_shared<Reservation>(testClient, testRoom2, testGuestCount,testId2, testBeginTime,
                                               testReservationDays1, C);
        testReservation3 = std::make_shared<Reservation>(testClient3, testRoom3, testGuestCount,testId3, testBeginTime,
                                               testReservationDays3, C);
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        currentRR->add(testReservation3);

        BOOST_REQUIRE_THROW(testReservations=RM.findClientReservations(testClient2),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.findClientReservations(testClient2),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testReservations.size()==0);

        BOOST_REQUIRE_THROW(testReservations=RM.findReservations([](const ReservationPtr &ptr){return ptr->getReservationDays()==30;}),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.findReservations([](const ReservationPtr &ptr){return ptr->getReservationDays()==30;}),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testReservations.size()==0);

        RM.endReservation(testId1);
        RM.endReservation(testId2);
        RM.endReservation(testId3);

        BOOST_REQUIRE_THROW(testReservations=RM.findAllReservations(),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.findAllReservations(),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testReservations.size()==0);
    }

    BOOST_AUTO_TEST_CASE(ChangeExtraBonusToBTest){
        ReservationManager RM(currentRR,archiveRR);
        pt::ptime localTimeSecondDay(pt::second_clock::local_time().date()-gr::days(1),pt::hours(12));
        pt::ptime localTimeLastDay(pt::second_clock::local_time().date()-gr::days(3),pt::hours(12));
        if(pt::second_clock::local_time()<pt::ptime(pt::second_clock::local_time().date(),pt::hours(12)))
        {
            localTimeSecondDay -= gr::days(1);
            localTimeLastDay -= gr::days(1);
        }

        testReservation = std::make_shared<Reservation>(testClient, testRoom, testGuestCount,testId1,testBeginTime+pt::minutes(1), 2, A);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        currentRR->add(testReservation);
        RM.changeReservationExtraBonusToB(testId1);
        BOOST_TEST(testReservation->getExtraBonus()==B);
        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+2*100);

        RM.endReservation(testId1);
        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeSecondDay,2,A);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2 = std::make_shared<Reservation>(testClient,testRoom2,testGuestCount,testId2,localTimeSecondDay,3,B);
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());
        testReservation3 = std::make_shared<Reservation>(testClient3,testRoom3,testGuestCount,testId3,localTimeSecondDay,4,A);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        currentRR->add(testReservation3);


        RM.changeReservationExtraBonusToB(testId1);
        RM.changeReservationExtraBonusToB(testId2);
        RM.changeReservationExtraBonusToB(testId3);


        BOOST_TEST(testReservation->getExtraBonus()==B);
        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+100);

        BOOST_TEST(testReservation2->getTotalReservationCost()==testRoom2->getFinalPricePerNight()*3+300);

        BOOST_TEST(testReservation3->getExtraBonus()==B);
        BOOST_TEST(testReservation3->getTotalReservationCost()==testRoom3->getFinalPricePerNight()*4+300);

        currentRR->remove(testReservation3);
        testReservation3 = std::make_shared<Reservation>(testClient3,testRoom3,testGuestCount,testId3,localTimeLastDay,4,A);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation3);

        RM.changeReservationExtraBonusToB(testId3);

        BOOST_TEST(testReservation3->getTotalReservationCost()==testRoom3->getFinalPricePerNight()*4+100);


    }
    BOOST_AUTO_TEST_CASE(ErrorChangeExtraBonusToBTest){
        ReservationManager RM(currentRR,archiveRR);
        pt::ptime localTimeReservationEnded(pt::second_clock::local_time().date()-gr::days(5),pt::hours(12));
        pt::ptime localTimeSecondDay(pt::second_clock::local_time().date()-gr::days(1),pt::hours(12));

        if(pt::second_clock::local_time()<pt::ptime(pt::second_clock::local_time().date(),pt::hours(12)))
        {
            localTimeSecondDay -= gr::days(1);
            localTimeReservationEnded -= gr::days(1);
        }

        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeReservationEnded,2,A);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2 = std::make_shared<Reservation>(testClient,testRoom2,testGuestCount,testId2,localTimeSecondDay,3,C);
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());

        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        BOOST_REQUIRE_THROW(RM.changeReservationExtraBonusToB(testId3),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.changeReservationExtraBonusToB(testId3),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Object";});

        BOOST_REQUIRE_THROW(RM.changeReservationExtraBonusToB(testId2),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.changeReservationExtraBonusToB(testId2),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR cant change to lower extra bonus";});




    }


    BOOST_AUTO_TEST_CASE(ChangeExtraBonusToCTest){
        ReservationManager RM(currentRR,archiveRR);
        pt::ptime localTimeSecondDay(pt::second_clock::local_time().date()-gr::days(1),pt::hours(12));
        pt::ptime localTimeLastDay(pt::second_clock::local_time().date()-gr::days(2),pt::hours(12));
        pt::ptime localTimeLastDay2(pt::second_clock::local_time().date()-gr::days(3),pt::hours(12));

        if(pt::second_clock::local_time()<pt::ptime(pt::second_clock::local_time().date(),pt::hours(12)))
        {
            localTimeSecondDay -= gr::days(1);
            localTimeLastDay -= gr::days(1);
            localTimeLastDay2 -= gr::days(1);
        }

        testReservation = std::make_shared<Reservation>(testClient, testRoom, testGuestCount,testId1, testBeginTime, 2, A);
        testReservation2 = std::make_shared<Reservation>(testClient2, testRoom2, testGuestCount,testId2, testBeginTime, 2, B);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        RM.changeReservationExtraBonusToC(testId1);
        RM.changeReservationExtraBonusToC(testId2);

        BOOST_TEST(testReservation->getExtraBonus()==C);
        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+2*250);
        BOOST_TEST(testReservation2->getExtraBonus()==C);
        BOOST_TEST(testReservation2->getTotalReservationCost()==testRoom2->getFinalPricePerNight()*2+2*250);


        RM.endReservation(testId1);
        RM.endReservation(testId2);
        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeSecondDay,2,A);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2 = std::make_shared<Reservation>(testClient,testRoom2,testGuestCount,testId2,localTimeSecondDay,3,A);
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());
        testReservation3 = std::make_shared<Reservation>(testClient3,testRoom3,testGuestCount,testId3,localTimeSecondDay,4,A);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        currentRR->add(testReservation3);


        RM.changeReservationExtraBonusToC(testId1);
        RM.changeReservationExtraBonusToC(testId2);
        RM.changeReservationExtraBonusToC(testId3);
        BOOST_TEST(testReservation->getExtraBonus()==C);
        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+250);

        BOOST_TEST(testReservation2->getExtraBonus()==C);
        BOOST_TEST(testReservation2->getTotalReservationCost()==testRoom2->getFinalPricePerNight()*3+500);

        BOOST_TEST(testReservation3->getExtraBonus()==C);
        BOOST_TEST(testReservation3->getTotalReservationCost()==testRoom3->getFinalPricePerNight()*4+750);

        currentRR->remove(testReservation);
        currentRR->remove(testReservation2);
        currentRR->remove(testReservation3);
        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeSecondDay,2,B);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2 = std::make_shared<Reservation>(testClient,testRoom2,testGuestCount,testId2,localTimeSecondDay,3,B);
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());
        testReservation3 = std::make_shared<Reservation>(testClient3,testRoom3,testGuestCount,testId3,localTimeSecondDay,4,B);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        currentRR->add(testReservation3);

        RM.changeReservationExtraBonusToC(testId1);
        RM.changeReservationExtraBonusToC(testId2);
        RM.changeReservationExtraBonusToC(testId3);

        BOOST_TEST(testReservation->getExtraBonus()==C);
        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+100+250);

        BOOST_TEST(testReservation2->getExtraBonus()==C);
        BOOST_TEST(testReservation2->getTotalReservationCost()==testRoom2->getFinalPricePerNight()*3+100+500);

        BOOST_TEST(testReservation3->getExtraBonus()==C);
        BOOST_TEST(testReservation3->getTotalReservationCost()==testRoom3->getFinalPricePerNight()*4+100+750);


        currentRR->remove(testReservation);
        currentRR->remove(testReservation2);
        currentRR->remove(testReservation3);
        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeSecondDay,2,C);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());
        testReservation2 = std::make_shared<Reservation>(testClient,testRoom2,testGuestCount,testId2,localTimeLastDay,3,B);
        testReservation2->setTotalReservationCost(testReservation2->calculateBaseReservationCost());
        testReservation3 = std::make_shared<Reservation>(testClient3,testRoom3,testGuestCount,testId3,localTimeLastDay2,4,A);
        testReservation3->setTotalReservationCost(testReservation3->calculateBaseReservationCost());
        currentRR->add(testReservation);
        currentRR->add(testReservation2);
        currentRR->add(testReservation3);

        RM.changeReservationExtraBonusToC(testId2);
        RM.changeReservationExtraBonusToC(testId3);

        BOOST_TEST(testReservation->getTotalReservationCost()==testRoom->getFinalPricePerNight()*2+500);
        BOOST_TEST(testReservation2->getTotalReservationCost()==testRoom2->getFinalPricePerNight()*3+200+250);
        BOOST_TEST(testReservation3->getTotalReservationCost()==testRoom3->getFinalPricePerNight()*4+250);


    }
    BOOST_AUTO_TEST_CASE(ErrorChangeExtraBonusToCTest){
        ReservationManager RM(currentRR,archiveRR);
        pt::ptime localTimeReservationEnded(pt::second_clock::local_time().date()-gr::days(5),pt::hours(12));
        pt::ptime localTimeSecondDay(pt::second_clock::local_time().date()-gr::days(1),pt::hours(12));

        if(pt::second_clock::local_time()<pt::ptime(pt::second_clock::local_time().date(),pt::hours(12)))
        {
            localTimeSecondDay -= gr::days(1);
            localTimeReservationEnded -= gr::days(1);
        }

        testReservation = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId1,localTimeReservationEnded,2,A);
        testReservation->setTotalReservationCost(testReservation->calculateBaseReservationCost());


        currentRR->add(testReservation);

        BOOST_REQUIRE_THROW(RM.changeReservationExtraBonusToC(testId3),ReservationError);
        BOOST_CHECK_EXCEPTION(RM.changeReservationExtraBonusToC(testId3),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Object";});


    }


BOOST_AUTO_TEST_SUITE_END()