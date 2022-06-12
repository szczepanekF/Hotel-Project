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
    RoomWithTerrace(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount,double initial_terraceSurface);///rzuca również wyjątek gdy rozmiar tarasu jest mniejszy lub równy zero
    std::string getInfo() const override;
    double getTerraceSurface() const;
    double getFinalPricePerNight() const override;///zwraca bazową cenę pomnożoną przez ułamek zależny od wielkości tarasu
    ~RoomWithTerrace() override;
};


#endif //INC_6_ROOMWITHTERRACE_H
