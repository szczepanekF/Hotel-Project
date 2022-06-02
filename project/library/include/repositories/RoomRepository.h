//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_ROOMREPOSITORY_H
#define HOTELPROJECT_ROOMREPOSITORY_H
#include "repositories/Repository.h"
#include "exceptions/RoomError.h"

class Room;

class RoomRepository:public Repository<Room,RoomError> {

public:
    RoomRepository();
    virtual ~RoomRepository() override;
};


#endif //HOTELPROJECT_ROOMREPOSITORY_H
