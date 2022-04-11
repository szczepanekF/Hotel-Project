//
// Created by student on 04.04.2022.
//

#ifndef CARRENTAL_RENT_H
#define CARRENTAL_RENT_H
#include <string>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Vehicle;
class Client;

class Client;

class Rent {
private:
    unsigned int id;
    Client *client;
    Vehicle *vehicle;
    pt::ptime beginTime;
    pt::ptime endTime=pt::not_a_date_time;
    unsigned int rentCost=0;
public:
    Rent(const unsigned int &InitialID, Client *Initial_client, Vehicle *Initial_vehicle,const pt::ptime &InitialbeginTime);
    const unsigned int &GetRentID() const;
    Vehicle *GetRentVehicle() const;
    Client *GetRentClient() const;
    std::string GetRentInfo() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    void endRent(const pt::ptime &InitialendTime);
    unsigned int getRentDays() const;
    unsigned int getRentCost() const;
};



#endif //CARRENTAL_RENT_H
