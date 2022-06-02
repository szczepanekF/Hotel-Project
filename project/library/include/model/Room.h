//
// Created by student on 21.05.2022.
//

#ifndef INC_6_ROOM_H
#define INC_6_ROOM_H
#include <string>
#include <memory>

enum extraBonusType{
    A=0,
    B=100,
    C=250,
    D=500,
    E=1000
};
class Room {
private:
    int roomNumber;
    double basePricePerNight;
    int bedCount;
    extraBonusType extraBonus;
public:


public:
    Room(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount, extraBonusType initial_extraBonus);
    virtual ~Room();

    int getRoomNumber() const;
    int getId() const;
    double getBasePricePerNight() const;
    double getPricePerNight() const;
    int getBedCount() const;
    extraBonusType getExtraBonus() const;
    //void setBasePricePerNight(double initial_basePricePerNight);
    void setBedCount(int initial_bedCount);
    void setExtraBonus(extraBonusType initial_extraBonus);


    virtual std::string getInfo() const;
    virtual double getFinalPricePerNight() const=0;


};



#endif //INC_6_ROOM_H
