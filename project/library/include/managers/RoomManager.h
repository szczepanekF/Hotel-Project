//
// Created by student on 05.06.2022.
//

#ifndef HOTELPROJECT_ROOMMANAGER_H
#define HOTELPROJECT_ROOMMANAGER_H

#include "repositories/RoomRepository.h"
#include "model/typedefs.h"
#include <memory>

class RoomManager {
private:
    RoomRepositoryPtr rooms;
public:
    RoomManager();
    explicit RoomManager(const RoomRepositoryPtr &initial_rooms);
    ~RoomManager();

    RoomPtr registerRoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);
    RoomPtr registerRoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount, double initial_terraceSurface);
//    void unregisterRoom(int roomNumber);
    RoomPtr getRoom(int roomNumber) const;
    std::vector<RoomPtr> findRooms(const RoomPredicate &predicate);
    std::vector<RoomPtr> findAllRooms();
};


#endif //HOTELPROJECT_ROOMMANAGER_H
