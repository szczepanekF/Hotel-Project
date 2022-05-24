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

class Reservation {
private:
    ClientPtr client;
    RoomPtr  room;
    int guestCount;
    ud::uuid id;
    pt::ptime beginTime;
    pt::ptime endTime;
    double totalReservationCost;


public:


    Reservation(const ClientPtr &client, const RoomPtr &room, int guestCount, const ud::uuid &id,
                const pt::ptime &beginTime, const pt::ptime &endTime);

    ~Reservation();

    const ClientPtr &getClient() const;
    const RoomPtr &getRoom() const;
    int getGuestCount() const;
    const ud::uuid &getId() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    double getTotalReservationCost() const;

    std::string getInfo() const;
    int getReservationDays() const;
    double calculateReservationCost() const;
    void setTotalReservationCost(double totalReservationCost);
};


#endif //HOTELPROJECT_RESERVATION_H
