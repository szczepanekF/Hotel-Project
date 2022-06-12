//
// Created by student on 21.05.2022.
//

#ifndef INC_6_ROOMWITHOUTTERRACE_H
#define INC_6_ROOMWITHOUTTERRACE_H
#include "Room.h"

class RoomWithoutTerrace: public Room {
public:
    RoomWithoutTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);
    ~RoomWithoutTerrace() override;
    std::string getInfo() const override;
    double getFinalPricePerNight() const override; ///zwraca bazową cenę bo ten typ pokoju nie ma tarasu
};


#endif //INC_6_ROOMWITHOUTTERRACE_H
