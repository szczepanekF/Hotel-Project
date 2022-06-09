//
// Created by student on 21.05.2022.
//

#ifndef INC_6_ROOMWITHTERRACE_H
#define INC_6_ROOMWITHTERRACE_H

#include "Room.h"
class RoomWithTerrace: public Room{
private:
    double terraceSurface;
public:
    RoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,double initial_terraceSurface);
    std::string getInfo() const override;
    double getTerraceSurface() const;
    double getFinalPricePerNight() const override;

    ~RoomWithTerrace() override;
};


#endif //INC_6_ROOMWITHTERRACE_H
