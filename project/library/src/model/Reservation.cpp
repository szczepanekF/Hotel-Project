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

Reservation::Reservation(const ClientPtr &initial_client, const RoomPtr &initial_room, unsigned int initial_guestCount,
                         const ud::uuid &initial_id, const pt::ptime &initial_beginTime,
                         unsigned int initial_reservationDays,
                         extraBonusType initial_bonus)
                         try : client(initial_client), room(initial_room), guestCount(initial_guestCount), id(initial_id),
                           beginTime(initial_beginTime), reservationsDays(initial_reservationDays),extraBonus(initial_bonus)
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
    if(initial_reservationDays <=0){
        throw ReservationError("Error Wrong reservation days");
    }

}catch(const ReservationError &e){

                         }

Reservation::~Reservation() = default;

const ClientPtr &Reservation::getClient() const {
    return client;
}

const RoomPtr &Reservation::getRoom() const {
    return room;
}

unsigned int Reservation::getGuestCount() const {
    return guestCount;
}

const ud::uuid &Reservation::getId() const {
    return id;
}

const pt::ptime &Reservation::getBeginTime() const {
    return beginTime;
}

 pt::ptime Reservation::getEndTime() const {
   pt::ptime ideal(getBeginTime().date(),pt::hours(12));
   if(ideal>getBeginTime()){
       return ideal+pt::hours((getReservationDays()-1)*24);
   }else{
       return ideal+pt::hours(getReservationDays()*24);
   }
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
    ss<<"\nFrom: "<<beginTime<<"  To: "<<getEndTime();
    ss<<"\nClient info: "<<client->getInfo();
    ss<<"\nRoom info: "<<room->getInfo();
    ss<<"\nExtra bonuses: "<<getExtraBonus()<<" Final price per night: "<<getPricePerNight();
    ss<<"\n--------------------------------------------------------------------------------------------------\n";
    return ss.str();
}

unsigned int Reservation::getReservationDays() const {
    return reservationsDays;
}

double Reservation::calculateBaseReservationCost() {
    double s= getPricePerNight()*getReservationDays();
    return s;
}

extraBonusType Reservation::getExtraBonus() const {
    return extraBonus;
}

void Reservation::setExtraBonus(extraBonusType extraBonus) {
    Reservation::extraBonus = extraBonus;
}

double Reservation::getPricePerNight() const {
    return room->getFinalPricePerNight()+getExtraBonus();
}
