#include "model/Reservation.h"
#include "model/Client.h"
#include "model/Room.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include "exceptions/ReservationError.h"
#include "exceptions/RoomError.h"
#include "exceptions/ClientError.h"

Reservation::Reservation(const ClientPtr &initial_client, const RoomPtr &initial_room, int initial_guestCount,
                         const ud::uuid &initial_id, const pt::ptime &initial_beginTime,
                         int initial_reservationDays,
                         extraBonusType initial_bonus)
                         try : client(initial_client), room(initial_room), guestCount(initial_guestCount), id(initial_id),
                           beginTime(initial_beginTime), reservationsDays(initial_reservationDays),extraBonus(initial_bonus),
                           totalReservationCost(0)
{
    if(initial_client == nullptr){
        throw ClientError("ERROR Null C_client");
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

}catch(const ReservationError &e){}

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

void Reservation::setTotalReservationCost(double new_totalReservationCost) {
    if(new_totalReservationCost < 0) throw ReservationError("Error Wrong reservation cost");
    totalReservationCost = new_totalReservationCost;
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

int Reservation::getReservationDays() const {
    return reservationsDays;
}

double Reservation::calculateBaseReservationCost() const {
    return getPricePerNight()*getReservationDays();
}

extraBonusType Reservation::getExtraBonus() const {
    return extraBonus;
}

void Reservation::setExtraBonus(extraBonusType new_extraBonus) {
    Reservation::extraBonus = new_extraBonus;
}

double Reservation::getPricePerNight() const {
    return room->getFinalPricePerNight()+getExtraBonus();
}

std::string Reservation::toDBInfo() const {
    std::string x;

    if (extraBonus == A) {
        x = '0';
    } else if (extraBonus == B) {
        x = '1';
    } else {
        x = '2';
    }


    std::stringstream ss;
    ss << client->getId() << "#" << room->getId() << "#" << room->getBedCount() << "#" << to_simple_string(beginTime)
       << "#" << reservationsDays << "#" <<x ;

    return ss.str();
}
