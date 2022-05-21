//
// Created by student on 21.05.2022.
//

#include "model/RoomWithTerrace.h"
#include <sstream>
RoomWithTerrace::RoomWithTerrace(int roomNumber, double basePricePerNight, int bedCount, extraBonusType extraBonus,
                                 double terraceSurface) : Room(roomNumber, basePricePerNight, bedCount, extraBonus),
                                                          terraceSurface(terraceSurface) {}

RoomWithTerrace::~RoomWithTerrace() {

}

std::string RoomWithTerrace::getInfo() const {
    std::stringstream ss;
    ss<<Room::getInfo()+" surface of a terrace: "+std::to_string(terraceSurface);
    return ss.str();
}

double RoomWithTerrace::getTerraceSurface() const {
    return terraceSurface;
}

double RoomWithTerrace::getFinalPricePerNight() const {
    if(terraceSurface<100)
        return getPricePerNight();
    else if(terraceSurface<200)
        return getPricePerNight()*1.2;
    else
        return getPricePerNight()*1.5;
}
