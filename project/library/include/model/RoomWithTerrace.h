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
    RoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount, extraBonusType initial_extraBonus,
                    double initial_terraceSurface);

    std::string getInfo() const override;
    double getTerraceSurface() const;
    double getFinalPricePerNight() const override;

    virtual ~RoomWithTerrace();
};


#endif //INC_6_ROOMWITHTERRACE_H
