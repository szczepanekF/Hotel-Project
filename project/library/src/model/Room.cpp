

#include "model/Room.h"
#include "exceptions/RoomError.h"
#include <sstream>
Room::Room(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount, extraBonusType initial_extraBonus)
try: roomNumber(initial_roomNumber), basePricePerNight(initial_basePricePerNight), bedCount(initial_bedCount), extraBonus(initial_extraBonus) {
    if(initial_basePricePerNight<=0){
        throw RoomError("ERROR Wrong base price");
    }
    if(initial_roomNumber<=0){
        throw RoomError("ERROR Wrong room number");
    }
    if(initial_bedCount<=0){
        throw RoomError("ERROR Wrong bed count");
    }
}catch (const RoomError &e){

}

Room::~Room() = default;

int Room::getRoomNumber() const {
    return roomNumber;
}
double Room::getBasePricePerNight() const {
    return basePricePerNight;
}
double Room::getPricePerNight() const {
    return basePricePerNight+extraBonus;
}

int Room::getBedCount() const {
    return bedCount;
}

extraBonusType Room::getExtraBonus() const {
    return extraBonus;
}

//void Room::setBasePricePerNight(double initial_basePricePerNight) {
//    if(initial_basePricePerNight <= 0)  throw RoomError("ERROR Wrong base price");
//    Room::basePricePerNight = initial_basePricePerNight;
//}

void Room::setBedCount(int initial_bedCount) {
    if(initial_bedCount <= 0)  throw RoomError("ERROR Wrong bed count");
    Room::bedCount = initial_bedCount;
}

std::string Room::getInfo() const {
    std::stringstream ss;
    ss<<"Room number: "<<roomNumber<<", bed count: "<<bedCount<<", base price per night: "<<basePricePerNight
    <<", extra bonuses: "<<extraBonus;
    return ss.str();
}

void Room::setExtraBonus(extraBonusType initial_extraBonus) {
    Room::extraBonus = initial_extraBonus;
}
