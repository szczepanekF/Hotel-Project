#include "model/RoomWithTerrace.h"
#include "exceptions/RoomError.h"
#include <sstream>

RoomWithTerrace::RoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,double initial_terraceSurface)
try: Room(initial_roomNumber, initial_basePricePerNight,initial_bedCount),terraceSurface(initial_terraceSurface) {
    if(initial_terraceSurface<=0){
        throw RoomError("Error Wrong terrace surface");
    }}catch (const RoomError &e){}

RoomWithTerrace::~RoomWithTerrace() = default;

std::string RoomWithTerrace::getInfo() const {
    std::stringstream ss;
    ss<<Room::getInfo()<<" surface of a terrace: "<<terraceSurface;
    return ss.str();
}

double RoomWithTerrace::getTerraceSurface() const {
    return terraceSurface;
}

double RoomWithTerrace::getFinalPricePerNight() const {
    if(terraceSurface<5)
        return getBasePricePerNight();
    else if(terraceSurface<10)
        return getBasePricePerNight()*1.2;
    else
        return getBasePricePerNight()*1.5;
}
