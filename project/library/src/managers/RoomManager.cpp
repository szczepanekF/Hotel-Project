//
// Created by student on 05.06.2022.
//

#include "managers/RoomManager.h"
#include "model/RoomWithTerrace.h"
#include "model/RoomWithoutTerrace.h"
#include <vector>

RoomManager::RoomManager() {

}

RoomManager::RoomManager(RoomRepository init_rooms) :rooms(init_rooms){

}

RoomManager::~RoomManager() {

}

RoomPtr RoomManager::RegisterRoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight,
                                                int initial_bedCount) {

    try{
        getRoom(initial_roomNumber);
    } catch(const RoomError &e){
        RoomPtr new_room = std::make_shared<RoomWithoutTerrace>(initial_roomNumber,initial_basePricePerNight,initial_bedCount);
        rooms.add(new_room);
        return new_room;
    }

    throw RoomError("ERROR Room already exists: "+getRoom(initial_roomNumber)->getInfo());
}

RoomPtr RoomManager::RegisterRoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,
                                     double initial_terraceSurface) {
    try{
        getRoom(initial_roomNumber);
    }catch(const RoomError &e){
        RoomPtr new_room = std::make_shared<RoomWithTerrace>(initial_roomNumber,initial_basePricePerNight,initial_bedCount,initial_terraceSurface);
        rooms.add(new_room);
        return new_room;
    }
    throw RoomError("ERROR Room already exists: "+getRoom(initial_roomNumber)->getInfo());
}

//void RoomManager::unregisterRoom(int roomNumber) {
//    RoomPtr remove_room = getRoom(roomNumber);
//    if(remove_room == nullptr)
//        throw RoomError("ERROR Null room");
//
//    rooms.remove(rooms.findById(roomNumber));
//}

RoomPtr RoomManager::getRoom(int roomNumber) const {
    return rooms.findById(roomNumber);
}

std::vector<RoomPtr> RoomManager::findAllRooms() {
    return rooms.findAll();
}

std::vector<RoomPtr> RoomManager::findRooms(std::function<bool(RoomPtr)> predicate) {
    return rooms.findBy(predicate);
}
