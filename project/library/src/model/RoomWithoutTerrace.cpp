#include "model/RoomWithoutTerrace.h"

RoomWithoutTerrace::~RoomWithoutTerrace() = default;

std::string RoomWithoutTerrace::getInfo() const {
    return Room::getInfo()+", no terrace";
}

double RoomWithoutTerrace::getFinalPricePerNight() const {
    return getBasePricePerNight();
}

RoomWithoutTerrace::RoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount)
: Room(initial_roomNumber, initial_basePricePerNight, initial_bedCount) {}
