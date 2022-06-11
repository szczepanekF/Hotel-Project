//
// Created by student on 24.05.2022.
//

#ifndef HOTELPROJECT_RESERVATION_H
#define HOTELPROJECT_RESERVATION_H
#include "model/typedefs.h"
#include <string>
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
namespace pt = boost::posix_time;
namespace ud = boost::uuids;
namespace gr = boost::gregorian;

enum extraBonusType{
    A=0,
    B=100,
    C=250,
};



class Reservation {
private:
    ClientPtr client;
    RoomPtr  room;
    int guestCount;
    int reservationsDays;
    ud::uuid id;
    pt::ptime beginTime;
    //pt::ptime endTime;
    double totalReservationCost;
    extraBonusType extraBonus;


public:


    Reservation(const ClientPtr &initial_client, const RoomPtr &initial_room, int initial_guestCount,
                const ud::uuid &initial_id, const pt::ptime &initial_beginTime, int initial_reservationDays,
                extraBonusType initial_bonus);

    ~Reservation();

    const ClientPtr &getClient() const;
    const RoomPtr &getRoom() const;
    int getGuestCount() const;
    const ud::uuid &getId() const;
    const pt::ptime &getBeginTime() const;
    pt::ptime getEndTime() const;
    double getTotalReservationCost() const;

    void setExtraBonus(extraBonusType new_extraBonus);
    extraBonusType getExtraBonus() const;
    std::string getInfo() const;
    int getReservationDays() const;
    double calculateBaseReservationCost();
    void setTotalReservationCost(double initial_totalReservationCost);
    double getPricePerNight() const;

};


#endif //HOTELPROJECT_RESERVATION_H
