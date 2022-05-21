

#include "model/Room.h"

#include <sstream>
Room::Room(int roomNumber, double basePricePerNight, int bedCount, extraBonusType extraBonus)
: roomNumber(roomNumber),basePricePerNight(basePricePerNight),bedCount(bedCount),extraBonus(extraBonus) {}

Room::~Room() {

}

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

void Room::setBasePricePerNight(double basePricePerNight) {
    if(basePricePerNight<=0) return;
    Room::basePricePerNight = basePricePerNight;
}

void Room::setBedCount(int bedCount) {
    if(bedCount <= 0) return;
    Room::bedCount = bedCount;
}

std::string Room::getInfo() const {
    std::stringstream ss;
    ss<<"Room number: "<<roomNumber<<", bed count: "<<bedCount<<", base price per night: "<<basePricePerNight
    <<", extra bonuses: "<<extraBonus;
    return ss.str();
}

void Room::setExtraBonus(extraBonusType extraBonus) {
    Room::extraBonus = extraBonus;
}
