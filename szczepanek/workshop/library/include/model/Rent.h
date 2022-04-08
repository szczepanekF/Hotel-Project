//
// Created by student on 04.04.2022.
//

#ifndef CARRENTAL_RENT_H
#define CARRENTAL_RENT_H
#include "Client.h"
#include "Vehicle.h"
#include <string>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;


class Client;
class Rent {
private:
    unsigned int id;
    Client * client;
    Vehicle * vehicle;
    pt::ptime beginTime;
    pt::ptime endTime = pt::not_a_date_time;

    unsigned int rentCost=0;

public:
    Rent(const unsigned int &init_id,Client *init_client,Vehicle *init_vehicle,pt::ptime init_beginTime);

    const std::string getRentInfo() const;

    const unsigned int &get_id() const;
    const Client * get_client() const;
    const Vehicle * get_vehicle() const;

    const pt::ptime get_beginTime() const;
    const pt::ptime get_endTime() const;


    unsigned int get_rentDays() const;
    const unsigned int get_rentCost() const;

    void endRent(pt::ptime new_endTime=pt::not_a_date_time);


};

#endif //CARRENTAL_RENT_H
