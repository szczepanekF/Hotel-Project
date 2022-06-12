#include "model/Room.h"
#include "exceptions/RoomError.h"
#include <sstream>

Room::Room(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount)
try: roomNumber(initial_roomNumber), basePricePerNight(initial_basePricePerNight), bedCount(initial_bedCount) {
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

int Room::getId() const {
    return roomNumber;
}


double Room::getBasePricePerNight() const {
    return basePricePerNight;
}


int Room::getBedCount() const {
    return bedCount;
}

void Room::setBedCount(int new_bedCount) {
    if(new_bedCount <= 0)  throw RoomError("ERROR Wrong bed count");
    Room::bedCount = new_bedCount;
}

std::string Room::getInfo() const {
    std::stringstream ss;
    ss<<"Room number: "<<roomNumber<<", bed count: "<<bedCount<<", base price per night: "<<basePricePerNight;
    return ss.str();
}



