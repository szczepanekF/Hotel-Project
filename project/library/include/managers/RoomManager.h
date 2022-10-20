//
// Created by student on 05.06.2022.
//

#ifndef HOTELPROJECT_ROOMMANAGER_H
#define HOTELPROJECT_ROOMMANAGER_H

#include "typedefs.h"
#include <vector>

class RoomRepository;

class RoomManager {
private:
    RoomRepositoryPtr rooms;
public:
    explicit RoomManager(const RoomRepositoryPtr &initial_rooms);
    ~RoomManager();

    RoomPtr registerRoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);
    ///przyjmuje wartości potrzebne do utworzenia pokoju bez tarasu, sprawdza czy pokój o takim numerze jest już w repozytorium, jeżeli tak rzuca wyjątek,
    ///w przeciwnym wypadku tworzy obiekt pokoju bez tarasu, dodaje go do repozutorium i zwraca wskaźnik na niego
    RoomPtr registerRoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount, double initial_terraceSurface);
    ///przyjmuje wartości potrzebne do utworzenia pokoju z tarasem, sprawdza czy pokój o takim numerze jest już w repozytorium, jeżeli tak rzuca wyjątek,
    ///w przeciwnym wypadku tworzy obiekt pokoju z tarasem, dodaje go do repozutorium i zwraca wskaźnik na niego
    RoomPtr getRoom(int roomNumber) const;

    std::vector<RoomPtr> findRooms(const RoomPredicate &predicate);
    std::vector<RoomPtr> findAllRooms();
};


#endif //HOTELPROJECT_ROOMMANAGER_H
