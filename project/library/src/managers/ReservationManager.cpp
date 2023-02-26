//
// Created by student on 06.06.2022.
//

#include "managers/ReservationManager.h"
#include "exceptions/ReservationError.h"
#include "exceptions/ClientError.h"
#include "exceptions/RoomError.h"
#include "repositories/ReservationRepository.h"
#include "repositories/ClientRepository.h"
#include "repositories/RoomRepository.h"
#include "model/Room.h"
#include "model/Client.h"
#include "boost/uuid/random_generator.hpp"
#include "managers/ClientManager.h"
#include "managers/RoomManager.h"


namespace gr = boost::gregorian;

ReservationManager::ReservationManager(const ReservationRepositoryPtr &currentReservations,
                                       const ReservationRepositoryPtr &archiveReservations) : currentReservations(
        currentReservations), archiveReservations(archiveReservations) {}

ReservationManager::~ReservationManager() {
   currentReservations->saveInformations("../../application_status/currentReservations.txt","CURRENT RESERVATIONS");
   archiveReservations->saveInformations("../../application_status/archiveReservations.txt","ARCHIVE RESERVATIONS");
}

ReservationPtr
ReservationManager::startReservation(const ClientPtr &client, const RoomPtr &room, unsigned int guestCount,
                                     const pt::ptime &beginTime, unsigned int reservationDays, extraBonusType bonus) {

    if(client->isArchive())
    {
        throw ReservationError("ERROR Client is archive");
    }

    try{
        findRoomReservations(room);
        if (!isRoomOccupied(room,beginTime,reservationDays)) {
            throw ReservationError("go to catch block");
        }
    }catch (const ReservationError &e){
        ud::random_generator gen;
        ud::uuid init_id =gen();
        while(true)
        {
            int i=0;
            try{
                currentReservations->findById(init_id);
            }catch(const ReservationError &e){
                i++;
            }
            try{
                archiveReservations->findById(init_id);
            }catch(const ReservationError &e){
                i++;
            }
            if(i==2)
            {
                break;
            }

             init_id =gen();
        }
        if(guestCount > room->getBedCount())
        {
            throw ReservationError("Error Too many guests");
        }
        if(reservationDays>client->getMaxDays()){
            throw ReservationError("Error Wrong reservation days");
        }

        pt::ptime ideal(beginTime.date(),pt::hours(13));
        ReservationPtr new_reservation = std::make_shared<Reservation>(client,room,guestCount,init_id,ideal,reservationDays,bonus);
        double price = new_reservation->calculateBaseReservationCost();
        if (client->acceptDiscount()) {
            price = price * (1 - calculateDiscount(client));
        }

        new_reservation->setTotalReservationCost(price);

        currentReservations->add(new_reservation);
        if (!reading) {
            client->setBalance(client->getBalance() - price);
        }

        return new_reservation;
    }
    throw ReservationError("ERROR room is occupied in this period");
}



ReservationPtr
ReservationManager::readReservation(const ClientPtr &client, const RoomPtr &room, unsigned int guestCount,
                                    const pt::ptime &beginTime, unsigned int reservationDays, extraBonusType bonus) {
    reading = true;
    ReservationPtr ptr = startReservation(client,room,guestCount,beginTime,reservationDays,bonus);
    reading = false;
    return ptr;
}



void ReservationManager::endReservation(const ud::uuid &id) {

    ReservationPtr reservation = currentReservations->findById(id);

    ClientPtr client = reservation->getClient();
    if(client->acceptDiscount())
    {
        client->setBalance(client->getBalance() + calculateDiscount(client) * reservation->getTotalReservationCost());
    }
    archiveReservations->add(reservation);
    currentReservations->remove(reservation);
}

std::vector<ReservationPtr> ReservationManager::findReservations(const ReservationPredicate &predicate) const {
    return currentReservations->findBy(predicate);
}

std::vector<ReservationPtr> ReservationManager::findAllReservations() const {
    return currentReservations->findAll();
}

std::vector<ReservationPtr> ReservationManager::findClientReservations(const ClientPtr &client) const {
    return currentReservations->findBy([client](const ReservationPtr &ptr){return ptr->getClient()==client;});
}

std::vector<ReservationPtr>  ReservationManager::findRoomReservations(const RoomPtr &room) const {
    return currentReservations->findBy([room](const ReservationPtr &ptr){return ptr->getRoom()==room;});
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



void ReservationManager::changeReservationExtraBonusToB(const ud::uuid &id) {
    ReservationPtr reservation = currentReservations->findById(id);
    ClientPtr client = reservation->getClient();
    extraBonusType type = B;
    double new_cost = calculatePriceDifferenceAfterChange(id,type);
    client->setBalance(client->getBalance()-new_cost);
    reservation->setExtraBonus(type);
    reservation->setTotalReservationCost(reservation->getTotalReservationCost()+new_cost);
    return;
}

void ReservationManager::changeReservationExtraBonusToC(const ud::uuid &id) {
    ReservationPtr reservation = currentReservations->findById(id);
    ClientPtr client = reservation->getClient();
    extraBonusType type = C;
    double new_cost = calculatePriceDifferenceAfterChange(id,type);
    client->setBalance(client->getBalance()-new_cost);
    reservation->setExtraBonus(type);
    reservation->setTotalReservationCost(reservation->getTotalReservationCost()+new_cost);
    return;
}

void ReservationManager::readReservationsFromServer(C_client* conn,ClientManagerPtr CM,RoomManagerPtr RM) {
    std::vector<std::vector<std::string>> resvsInfo = currentReservations->readInfo(conn,GET_RESERVATIONS);
    ClientPtr client;
    RoomPtr  room;
    unsigned int guest_count;
    unsigned int days_of_res;
    extraBonusType type;
    for(int i=0;i<resvsInfo.size();i++) {
        client = CM->getClient(resvsInfo[i][0]);
        room = RM->getRoom(std::stoi(resvsInfo[i][1]));
        guest_count = std::stoi(resvsInfo[i][2]);
        pt::ptime begin_date = pt::time_from_string(resvsInfo[i][3]);

        days_of_res = std::stoi(resvsInfo[i][4]);

        if(resvsInfo[i][5] == "2")
            type = C;
        else if(resvsInfo[i][5] == "1")
            type = B;
        else
            type = A;
        try {
            readReservation(client, room, guest_count, begin_date, days_of_res, type);
        } catch (ReservationError &e) {
            std::cout<< e.what();
        }
    }
}

bool ReservationManager::isRoomOccupied(const RoomPtr &room, const pt::ptime& beginTime, unsigned int resDays) {
    std::vector<ReservationPtr> resvs = findRoomReservations(room);
    return std::find_if(resvs.begin(),resvs.end(),[beginTime,resDays](const ReservationPtr& ptr){
        if (ptr->getEndTime().date() < beginTime.date() ) {
            return false;
        } else if ((beginTime+ pt::hours(resDays*24)).date()  < ptr->getBeginTime().date()) {
            return false;
        }
        return true;}) != resvs.end();

}


void ReservationManager::addReservationToDB(C_client *conn, std::string &infos) {
    if (conn->getConnSuccess() < 0) {
        return ;
    }
    conn->saveInfo(infos);
}

void ReservationManager::setReservationArchive(const ud::uuid &id) {
    ReservationPtr reservation = currentReservations->findById(id);
    archiveReservations->add(reservation);
    currentReservations->remove(reservation);
}

void ReservationManager::removeFromDB(C_client *conn, std::string &infos) {
    if (conn->getConnSuccess() < 0) {
        return ;
    }
    conn->deleteReservation(infos);
}

double ReservationManager::calculatePriceDifferenceAfterChange(const ud::uuid &id, extraBonusType new_Type) {
    if (new_Type == A)
        return 0;
    ReservationPtr reservation = currentReservations->findById(id);
    if(reservation->getExtraBonus() > new_Type) throw ReservationError("ERROR cant change to lower extra bonus");

    extraBonusType bonus = reservation->getExtraBonus();

    double new_cost;
    double old_cost;
    if(pt::second_clock::local_time()<=reservation->getBeginTime()){
        old_cost = reservation->calculateBaseReservationCost();
        reservation->setExtraBonus(new_Type);
        new_cost = reservation->calculateBaseReservationCost();
        reservation->setExtraBonus(bonus);
        return new_cost - old_cost;
    }

    pt::ptime ideal(reservation->getBeginTime().date(),pt::hours(12));

    if(ideal > reservation->getBeginTime())
        ideal -= gr::days(1);

    pt::time_period period(ideal,pt::second_clock::local_time());

    long daysBeforeChange = period.length().hours()/24;
    long daysAfterChange= reservation->getReservationDays()-daysBeforeChange;

    old_cost = reservation->getPricePerNight()*(double)daysAfterChange;
    reservation->setExtraBonus(new_Type);
    new_cost = reservation->getPricePerNight()*(double)daysAfterChange;
    reservation->setExtraBonus(bonus);
    return new_cost-old_cost;
}

void ReservationManager::removeReservation(const ud::uuid &id) {
    ReservationPtr ptr = currentReservations->findById(id);
    currentReservations->remove(ptr);
}

void ReservationManager::updateExtraBonusToDB(C_client* conn,const ReservationPtr &ptr) {
    if (conn->getConnSuccess() < 0) {
        return ;
    }
    std::string type;

    if (ptr->getExtraBonus() == A) {
        type = "0";
    } else if (ptr->getExtraBonus() == B) {
        type = "1";
    } else {
        type = "2";
    }

    std::stringstream ss;
    ss << ptr->getClient()->getId() << "#" << ptr->getRoom()->getId() << "#" << ptr->getBeginTime() << "#" << type;
    conn->updateResType(ss.str());

}


