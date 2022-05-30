//
// Created by student on 21.05.2022.
//

#include "model/RoomWithoutTerrace.h"

RoomWithoutTerrace::~RoomWithoutTerrace() = default;

std::string RoomWithoutTerrace::getInfo() const {
    return Room::getInfo()+", no terrace";
}

double RoomWithoutTerrace::getFinalPricePerNight() const {
    return getBasePricePerNight();
}

RoomWithoutTerrace::RoomWithoutTerrace(int roomNumber, double basePricePerNight, int bedCount)
: Room(roomNumber, basePricePerNight, bedCount) {}
