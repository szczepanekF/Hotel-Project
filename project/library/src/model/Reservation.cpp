//
// Created by student on 24.05.2022.
//

#include "model/Reservation.h"
#include "model/Client.h"
#include "model/Room.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>

Reservation::Reservation(const ClientPtr &client, const RoomPtr &room, int guestCount, const ud::uuid &id,
                         const pt::ptime &beginTime, const pt::ptime &endTime)
                         : client(client), room(room),guestCount(guestCount), id(id),
                         beginTime(beginTime),endTime(endTime)
{
    if(client == nullptr){
//        throw ClientError("NULL CLIENT ERROR");
    }
    if(room == nullptr){
//        throw ClientError("NULL ROOM ERROR");
    }
    if(guestCount <= 0){
//        throw ReservationError("INVALID GUEST COUNT");
    }
    if(beginTime == pt::not_a_date_time){
//        throw ReservationError("BEGIN TIME NOT GIVEN");
    }
    if(endTime == pt::not_a_date_time || endTime < beginTime){
//        throw ReservationError("END TIME NOT GIVEN");
    }
    if(guestCount > room->getBedCount())
    {
//        throw ReservationError("TOO MANY GUESTS")
    }
    calculateReservationCost();
}

Reservation::~Reservation() {

}

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

//void Reservation::setTotalReservationCost(double totalReservationCost) {
//    totalReservationCost = totalReservationCost;
//}

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
//    if(endTime == pt::not_a_date_time)
//        return 0;
    pt::time_period period(beginTime,endTime);
//    if(endTime-beginTime<=pt::seconds(59))
//        return 0;
//    else
    return period.length().hours()/24 + 1;
}

void Reservation::calculateReservationCost() {
    totalReservationCost = client->getBill()+room->getFinalPricePerNight()*getReservationDays();
//    return totalReservationCost;
}
