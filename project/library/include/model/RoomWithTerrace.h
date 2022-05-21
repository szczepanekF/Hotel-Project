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
    RoomWithTerrace(int roomNumber, double basePricePerNight, int bedCount, extraBonusType extraBonus,
                    double terraceSurface);

    std::string getInfo() const override;
    double getTerraceSurface() const;
    double getFinalPricePerNight() const override;

    virtual ~RoomWithTerrace();
};


#endif //INC_6_ROOMWITHTERRACE_H
