//
// Created by student on 16.02.2023.
//

#ifndef HOTELPROJECT_RESERVATIONITEMDATA_H
#define HOTELPROJECT_RESERVATIONITEMDATA_H

#include <boost/date_time.hpp>
#include "model/Reservation.h"

namespace pt = boost::posix_time;
struct ReservationItemData
{
    int roomNr;
    pt::ptime begin;
    pt::ptime end;
    int guests;
    extraBonusType type_of_res;

};
#endif //HOTELPROJECT_RESERVATIONITEMDATA_H
