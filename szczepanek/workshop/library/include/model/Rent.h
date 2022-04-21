//
// Created by student on 04.04.2022.
//

#ifndef CARRENTAL_RENT_H
#define CARRENTAL_RENT_H
#include "Client.h"
#include "Vehicle.h"
#include <string>
#include <boost/date_time.hpp>
#include "typedefs.h"

namespace pt = boost::posix_time;


class Client;
class Rent {
private:
    unsigned int id;
    ClientPtr client;
    VehiclePtr vehicle;
    pt::ptime beginTime;
    pt::ptime endTime = pt::not_a_date_time;
    unsigned int rentCost=0;

public:
    Rent(const unsigned int &init_id,ClientPtr init_client,VehiclePtr init_vehicle,pt::ptime init_beginTime);

    const std::string getRentInfo() const;

    const unsigned int &get_id() const;
    const ClientPtr get_client() const;
    const VehiclePtr get_vehicle() const;
    const pt::ptime &get_beginTime() const;
    const pt::ptime &get_endTime() const;

    const unsigned int &get_rentCost() const;

    unsigned int get_rentDays() const;


    void endRent(pt::ptime new_endTime=pt::not_a_date_time);
};

#endif //CARRENTAL_RENT_H
