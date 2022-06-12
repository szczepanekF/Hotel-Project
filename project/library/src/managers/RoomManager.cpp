//
// Created by student on 05.06.2022.
//

#include "managers/RoomManager.h"
#include "model/RoomWithTerrace.h"
#include "model/RoomWithoutTerrace.h"
#include "exceptions/RoomError.h"
#include <vector>
#include "repositories/RoomRepository.h"

RoomManager::RoomManager(const RoomRepositoryPtr &initial_rooms) : rooms(initial_rooms){
}



RoomManager::~RoomManager() {
   rooms->saveInformations("../../application_status/rooms.txt","ROOMS");
}



RoomPtr RoomManager::registerRoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight,
                                                int initial_bedCount) {

    try{
        getRoom(initial_roomNumber);
    } catch(const RoomError &e){
        RoomPtr new_room = std::make_shared<RoomWithoutTerrace>(initial_roomNumber,initial_basePricePerNight,initial_bedCount);
        rooms->add(new_room);
        return new_room;
    }

    throw RoomError("ERROR already exists: "+getRoom(initial_roomNumber)->getInfo());
}

RoomPtr RoomManager::registerRoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,
                                             double initial_terraceSurface) {
    try{
        getRoom(initial_roomNumber);
    }catch(const RoomError &e){
        RoomPtr new_room = std::make_shared<RoomWithTerrace>(initial_roomNumber,initial_basePricePerNight,initial_bedCount,initial_terraceSurface);
        rooms->add(new_room);
        return new_room;
    }
    throw RoomError("ERROR already exists: "+getRoom(initial_roomNumber)->getInfo());
}

RoomPtr RoomManager::getRoom(int roomNumber) const {
    return rooms->findById(roomNumber);
}

std::vector<RoomPtr> RoomManager::findAllRooms() {
    return rooms->findAll();
}

std::vector<RoomPtr> RoomManager::findRooms(const RoomPredicate &predicate) {
    return rooms->findBy(predicate);
}
