//
// Created by student on 21.05.2022.
//

#include "model/RoomWithoutTerrace.h"

RoomWithoutTerrace::~RoomWithoutTerrace() {

}

std::string RoomWithoutTerrace::getInfo() const {
    return Room::getInfo()+", no terrace";
}

double RoomWithoutTerrace::getFinalPricePerNight() const {
    return getPricePerNight();
}

RoomWithoutTerrace::RoomWithoutTerrace(int roomNumber, double basePricePerNight, int bedCount,
                                       extraBonusType extraBonus) : Room(roomNumber, basePricePerNight, bedCount,
                                                                         extraBonus) {}
