#ifndef HOTELPROJECT_ROOMREPOSITORY_H
#define HOTELPROJECT_ROOMREPOSITORY_H
#include "repositories/Repository.h"

class Room;
class RoomError;

class RoomRepository:public Repository<Room,RoomError> {

public:
    RoomRepository();
    ~RoomRepository() override;
};


#endif //HOTELPROJECT_ROOMREPOSITORY_H
