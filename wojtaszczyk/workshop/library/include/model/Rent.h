#ifndef CARRENTAL_RENT_H
#define CARRENTAL_RENT_H
#include <string>
#include <boost/date_time.hpp>
#include "typedef.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Vehicle;
class Client;

class Client;

class Rent {
private:
    unsigned int id;
    ClientPtr client;
    VehiclePtr vehicle;
    pt::ptime beginTime;
    pt::ptime endTime=pt::not_a_date_time;
    unsigned int rentCost=0;
public:
    Rent(const unsigned int &InitialID, ClientPtr Initial_client, VehiclePtr Initial_vehicle,const pt::ptime &InitialbeginTime);
    const unsigned int &getRentID() const;
    VehiclePtr getRentVehicle() const;
    ClientPtr getRentClient() const;
    std::string getRentInfo() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    void endRent(const pt::ptime &InitialendTime);
    unsigned int getRentDays() const;
    const unsigned int &getRentCost() const;
};



#endif //CARRENTAL_RENT_H
