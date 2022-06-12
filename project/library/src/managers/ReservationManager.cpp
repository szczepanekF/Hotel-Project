//
// Created by student on 06.06.2022.
//

#include "managers/ReservationManager.h"
#include "exceptions/ReservationError.h"
#include "repositories/ReservationRepository.h"
#include "model/Room.h"
#include "model/Client.h"
#include <fstream>
#include "boost/uuid/random_generator.hpp"
ReservationManager::ReservationManager(const ReservationRepositoryPtr &currentReservations,
                                       const ReservationRepositoryPtr &archiveReservations) : currentReservations(
        currentReservations), archiveReservations(archiveReservations) {}

ReservationManager::ReservationManager() {}

ReservationManager::~ReservationManager() {
    std::ofstream plik("../../application_status/currentReservations.txt");
    std::ofstream plik2("../../application_status/archiveReservations.txt");

    plik<<"CURRENT RENTS: ";
    for(int i=0;i<currentReservations->size();i++)
    {
        plik<<currentReservations->get(i)->getInfo();
    }
    plik2<<"ARCHIVE RENTS:";
    for(int i=0;i<archiveReservations->size();i++)
    {
        plik2<<archiveReservations->get(i)->getInfo();
    }
    plik.close();
    plik2.close();
}

ReservationPtr
ReservationManager::startReservation(const ClientPtr &client, const RoomPtr &room, unsigned int guestCount,
                                     const pt::ptime beginTime, unsigned int reservationDays, extraBonusType bonus) {
    if(client->isArchive()) throw ReservationError("ERROR Client is archive");



    try{

//        while(currentReservations->findById(init_id) != nullptr){
//            ud::random_generator gen;
//            ud::uuid init_id =gen();
//        }
        findRoomReservation(room);
    }catch (const ReservationError &e){
        ud::random_generator gen;
        ud::uuid init_id =gen();
        while(true)
        {
            try{
                currentReservations->findById(init_id);
                archiveReservations->findById(init_id);
            }
            catch(const ReservationError &e){
                break;
            }
            ud::random_generator gen;
            ud::uuid init_id =gen();
        }
        if(beginTime<pt::second_clock::local_time())
        {
            throw ReservationError("Error Wrong begin time");
        }
        if(guestCount > room->getBedCount())
        {
            throw ReservationError("Error Too many guests");
        }
        if(reservationDays>client->getMaxDays()){
            throw ReservationError("Error Wrong reservation days");
        }
        ReservationPtr new_reservation = std::make_shared<Reservation>(client,room,guestCount,init_id,beginTime,reservationDays,bonus);
//        room->setInUse(true);
        if(client->getBill()+new_reservation->calculateBaseReservationCost()<0)
        {
            new_reservation->setTotalReservationCost(0);
        }else{
            new_reservation->setTotalReservationCost(client->getBill()+new_reservation->calculateBaseReservationCost());
        }

        client->setBill(0);
        currentReservations->add(new_reservation);


        return new_reservation;
    }
    throw ReservationError("ERROR already exists: "+findRoomReservation(room)->getInfo());
}

void ReservationManager::endReservation(const ud::uuid id) {
    ReservationPtr reservation = currentReservations->findById(id);
//    reservation->getRoom()->setInUse(false);
    ClientPtr client = reservation->getClient();
    client->setBill(client->getBill()-calculateDiscount(client)*reservation->getTotalReservationCost());
    archiveReservations->add(reservation);
    currentReservations->remove(reservation);
}

std::vector<ReservationPtr> ReservationManager::findReservations(ReservationPredicate predicate) const {
    return currentReservations->findBy(predicate);
}

std::vector<ReservationPtr> ReservationManager::findAllReservations() const {
    return currentReservations->findAll();
}

std::vector<ReservationPtr> ReservationManager::findClientReservations(const ClientPtr &client) const {
    return currentReservations->findBy([client](const ReservationPtr &ptr){return ptr->getClient()==client;});
}

ReservationPtr ReservationManager::findRoomReservation(const RoomPtr &room) const {
    return currentReservations->findBy([room](const ReservationPtr &ptr){return ptr->getRoom()==room;})[0];
}

double ReservationManager::calculateDiscount(const ClientPtr &client) const {
    double discount = 0;
    int days = 0;
    std::vector<ReservationPtr> clientReservations;
    try{
        clientReservations = archiveReservations->findBy([client](const ReservationPtr &ptr){return ptr->getClient()==client;});
    }catch(const HotelError &e){
        return 0;
    }

    for(int i=0;i<clientReservations.size();i++)
    {
        days += clientReservations[i]->getReservationDays();
    }
    if(days>=60)
        discount = 0.07;
    else if(days>=21)
        discount = 0.05;
    else if(days>=7)
        discount = 0.02;
    return discount;
}



void ReservationManager::changeReservationExtraBonusToB(const ud::uuid id) {
    ReservationPtr reservation = currentReservations->findById(id);
    if(reservation->getExtraBonus()==C) throw ReservationError("ERROR cant change to lower extra bonus");

    if(pt::second_clock::local_time()>reservation->getEndTime()) throw ReservationError("ERROR Reservation ended");

    int new_cost=0;
    if(pt::second_clock::local_time()<=reservation->getBeginTime()){
        new_cost=(reservation->getTotalReservationCost()-reservation->getPricePerNight()*reservation->getReservationDays());
        reservation->setExtraBonus(B);
        new_cost+=reservation->getPricePerNight()*reservation->getReservationDays();
        reservation->setTotalReservationCost(new_cost);
        return;
    }

    pt::ptime ideal(reservation->getBeginTime().date(),pt::hours(12));
    if(ideal>reservation->getBeginTime())
        ideal -=gr::days(1);
    pt::time_period period(ideal,pt::second_clock::local_time());


    int daysBeforeChange = period.length().hours()/24;
    int daysAfterChange= reservation->getReservationDays()-daysBeforeChange;



    new_cost = reservation->getTotalReservationCost()-reservation->getPricePerNight()*daysAfterChange;
    reservation->setExtraBonus(B);
    new_cost += reservation->getPricePerNight()*daysAfterChange;

    reservation->setTotalReservationCost(new_cost);
}

void ReservationManager::changeReservationExtraBonusToC(const ud::uuid id) {
    ReservationPtr reservation = currentReservations->findById(id);
    if(pt::second_clock::local_time()>reservation->getEndTime()) throw ReservationError("ERROR Reservation ended");
    pt::ptime ideal(reservation->getBeginTime().date(),pt::hours(12));


    int new_cost=0;
    if(pt::second_clock::local_time()<reservation->getBeginTime()){
        new_cost=(reservation->getTotalReservationCost()-reservation->getPricePerNight()*reservation->getReservationDays());
        reservation->setExtraBonus(C);
        new_cost+=reservation->getPricePerNight()*reservation->getReservationDays();
        reservation->setTotalReservationCost(new_cost);
        return;
    }
    pt::time_period period(ideal,pt::second_clock::local_time());

    int daysBeforeChange = period.length().hours()/24;
    int daysAfterChange= reservation->getReservationDays()-daysBeforeChange;

    new_cost = reservation->getTotalReservationCost()-reservation->getPricePerNight()*daysAfterChange ;
    reservation->setExtraBonus(C);
    new_cost += reservation->getPricePerNight()*daysAfterChange;
    reservation->setTotalReservationCost(new_cost);
}



