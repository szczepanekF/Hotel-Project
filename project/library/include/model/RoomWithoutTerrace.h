//
// Created by student on 21.05.2022.
//

#ifndef INC_6_ROOMWITHOUTTERRACE_H
#define INC_6_ROOMWITHOUTTERRACE_H
#include "Room.h"

class RoomWithoutTerrace: public Room {
public:
    RoomWithoutTerrace(int roomNumber, double basePricePerNight, int bedCount);
    ~RoomWithoutTerrace() override;
    std::string getInfo() const override;
    double getFinalPricePerNight() const override;
};


#endif //INC_6_ROOMWITHOUTTERRACE_H
