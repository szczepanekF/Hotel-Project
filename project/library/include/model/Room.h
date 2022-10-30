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
    Room(int initial_roomNumber, double initial_basePricePerNight, int initial_bedCount);///rzuca wyjątek gdy którakolwiek z wartości jest mniejsza lub równa 0
    virtual ~Room();

    int getId() const; ///zwraca numer pokoju
    double getBasePricePerNight() const;
    int getBedCount() const;

    void setBedCount(int new_bedCount);

    virtual std::string getInfo() const;
    virtual double getFinalPricePerNight() const=0;///cena bazowa za noc zależna jest również od tego czy pokój ma taras i od jego rozmiaru

};



#endif //INC_6_ROOM_H
