//
// Created by student on 21.05.2022.
//

#ifndef INC_6_ROOM_H
#define INC_6_ROOM_H
#include <string>
#include <memory>

class Room {
private:
    int roomNumber;
    double basePricePerNight;
    int bedCount;

public:
    Room(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);
    virtual ~Room();
    int getRoomNumber() const;
    double getBasePricePerNight() const;
    int getBedCount() const;
    //void setBasePricePerNight(double initial_basePricePerNight);
    void setBedCount(int initial_bedCount);
    virtual std::string getInfo() const;
    virtual double getFinalPricePerNight() const=0;


};



#endif //INC_6_ROOM_H
