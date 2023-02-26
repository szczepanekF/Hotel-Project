#ifndef HOTELPROJECT_RESERVATION_H
#define HOTELPROJECT_RESERVATION_H
#include "typedefs.h"
#include <string>
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>

namespace pt = boost::posix_time;
namespace ud = boost::uuids;

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
    double totalReservationCost;
    extraBonusType extraBonus;
public:


    Reservation(const ClientPtr &initial_client, const RoomPtr &initial_room, int initial_guestCount,
                const ud::uuid &initial_id, const pt::ptime &initial_beginTime, int initial_reservationDays,
                extraBonusType initial_bonus); ///rzuca wyjątek gdy gdy initial_client==nullptr, initial_room==nullptr, initial_guestCount<=0, initial_reservationDays<=0 lub initial_beginTime==not_a_date_time

    ~Reservation();

    const ClientPtr &getClient() const;
    const RoomPtr &getRoom() const;
    int getGuestCount() const;
    const ud::uuid &getId() const; ///zwraca ID rezerwacji
    const pt::ptime &getBeginTime() const;
    pt::ptime getEndTime() const; ///oblicza i zwraca którego dnia kończy się rezerwacja (zgodnie z zasadą że doba hotelowa zaczyna się o 12:00)
    double getTotalReservationCost() const;

    void setExtraBonus(extraBonusType new_extraBonus);
    extraBonusType getExtraBonus() const;
    std::string getInfo() const;
    int getReservationDays() const;
    double calculateBaseReservationCost() const; ///oblicza koszt rezerwacji, który jest iloczynem ceny za noc i ilością nocy
    void setTotalReservationCost(double new_totalReservationCost);
    double getPricePerNight() const; ///zwraca sumę ceny pokoju i bonusu, która jest ostateczną ceną za jedną noc rezerwacji
    std::string toDBInfo() const;
};


#endif //HOTELPROJECT_RESERVATION_H
