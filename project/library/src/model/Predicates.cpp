#include "model/Predicates.h"
#include <cctype>
#include "exceptions/ClientError.h"
#include "model/Client.h"
#include "exceptions/RoomError.h"
#include "model/Room.h"
#include "model/Reservation.h"
#include "exceptions/ReservationError.h"

namespace pt = boost::posix_time;

ClientLastNamePredicate::ClientLastNamePredicate(const std::string &initial_spattern) try: spattern(initial_spattern) {
    if(initial_spattern.empty()){
        throw ClientError("ERROR Empty pattern");
    }
    else{
        spattern[0]=std::toupper(spattern[0]);
        pattern=spattern+"(.*)";
    }
}catch(const ClientError &e){}


bool ClientLastNamePredicate::operator()(const ClientPtr &ptr) const {
    return std::regex_match(ptr->getLastName(),pattern);
}

RoomBasePricePredicate::RoomBasePricePredicate(double initial_patternprice) try: patternprice(initial_patternprice) {
    if(initial_patternprice<=0){
        throw RoomError("ERROR Wrong pattern price");
    }
}catch (const RoomError &e){}

bool RoomBasePricePredicate::operator()(const RoomPtr &ptr) const {
    return ptr->getBasePricePerNight()>=patternprice;
}

ReservationBeginTimePredicate::ReservationBeginTimePredicate(const boost::posix_time::ptime &initial_patternBeginTime)
        try: patternBeginTime(initial_patternBeginTime) {
            if(initial_patternBeginTime==pt::not_a_date_time){
                throw ReservationError("Error Begin time not given");
            }
        }catch(const ReservationError &e){}

bool ReservationBeginTimePredicate::operator()(const ReservationPtr &ptr) const {
    return ptr->getBeginTime()>=patternBeginTime;
}
