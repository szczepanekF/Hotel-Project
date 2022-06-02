//
// Created by student on 24.05.2022.
//

#include "model/Reservation.h"
#include "model/Client.h"
#include "model/Room.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include "exceptions/ReservationError.h"
#include "exceptions/RoomError.h"
#include "exceptions/ClientError.h"

Reservation::Reservation(const ClientPtr &initial_client, const RoomPtr &initial_room, int initial_guestCount, const ud::uuid &initial_id,
                         const pt::ptime &initial_beginTime, const pt::ptime &initial_endTime)
                         : client(initial_client), room(initial_room), guestCount(initial_guestCount), id(initial_id),
                           beginTime(initial_beginTime), endTime(initial_endTime)
{
    if(initial_client == nullptr){
        throw ClientError("ERROR Null client");
    }
    if(initial_room == nullptr){
        throw RoomError("Error Null room");
    }
    if(initial_guestCount <= 0){
        throw ReservationError("ERROR Wrong guest count");
    }
    if(initial_beginTime == pt::not_a_date_time){
       throw ReservationError("Error Begin time not given");
    }
    if(initial_endTime == pt::not_a_date_time || initial_endTime < initial_beginTime){
        throw ReservationError("Error End time not given");
    }
    if(initial_guestCount > initial_room->getBedCount())
    {
        throw ReservationError("Error Too many guests");
    }
    setTotalReservationCost(calculateBaseReservationCost());
}

Reservation::~Reservation() = default;

const ClientPtr &Reservation::getClient() const {
    return client;
}

const RoomPtr &Reservation::getRoom() const {
    return room;
}

int Reservation::getGuestCount() const {
    return guestCount;
}

const ud::uuid &Reservation::getId() const {
    return id;
}

const pt::ptime &Reservation::getBeginTime() const {
    return beginTime;
}

const pt::ptime &Reservation::getEndTime() const {
    return endTime;
}

double Reservation::getTotalReservationCost() const {
    return totalReservationCost;
}

void Reservation::setTotalReservationCost(double initial_totalReservationCost) {
    if(initial_totalReservationCost<=0) throw ReservationError("Error Wrong reservation cost");
    totalReservationCost = initial_totalReservationCost;
}

std::string Reservation::getInfo() const {
    std::stringstream ss;
    ss<<"\n--------------------------------------------------------------------------------------------------\n";
    ss<<"Reservation id: "<<ud::to_string(id)<<", number of guests: "<<guestCount;
    ss<<"\nFrom: "<<beginTime<<"  To: "<<endTime;
    ss<<"\nClient info: "<<client->getInfo();
    ss<<"\nRoom info: "<<room->getInfo();
    ss<<"\n--------------------------------------------------------------------------------------------------\n";
    return ss.str();
}

int Reservation::getReservationDays() const {

    pt::time_period period(beginTime,endTime);
//    if(endTime-beginTime<=pt::seconds(59))
//        return 0;
//    else
    return period.length().hours()/24 + 1;
}

double Reservation::calculateBaseReservationCost() {
    double s= client->getBill()+room->getFinalPricePerNight()*getReservationDays();
    return s;
}
