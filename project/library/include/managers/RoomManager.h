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
    RoomManager(const RoomRepositoryPtr &init_rooms);
    ~RoomManager();

    RoomPtr RegisterRoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);
    RoomPtr RegisterRoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,double initial_terraceSurface);
//    void unregisterRoom(int roomNumber);
    RoomPtr getRoom(int roomNumber) const;
    std::vector<RoomPtr> findRooms(RoomPredicate predicate);
    std::vector<RoomPtr> findAllRooms();
};


#endif //HOTELPROJECT_ROOMMANAGER_H
