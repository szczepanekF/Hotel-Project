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

void RoomManager::readRoomsFromServer(C_client* conn) {
    std::vector<std::vector<std::string>> roomsInfo = rooms->readInfo(conn,GET_ROOMS);
    int room_nr;
    double price;
    double terrace_sur;
    int bed_count;



    for(int i=0;i<roomsInfo.size();i++) {
        room_nr = std::stoi(roomsInfo[i][0]);
        price = std::stod(roomsInfo[i][1]);
        bed_count = std::stoi(roomsInfo[i][2]);
        if(roomsInfo[i][3] == "None") {
            registerRoomWithoutTerrace(room_nr, price, bed_count);
        }
        else{
            terrace_sur = std::stod(roomsInfo[i][3]);
            registerRoomWithTerrace(room_nr, price, bed_count,terrace_sur);
        }
    }
}

