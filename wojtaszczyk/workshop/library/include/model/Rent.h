#ifndef CARRENTAL_RENT_H
#define CARRENTAL_RENT_H
#include <string>
#include <boost/date_time.hpp>
#include "typedef.h"
#include "exceptions/RentException.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_serialize.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;


class Rent {
private:
    boost::uuids::uuid id;
    ClientPtr client;
    VehiclePtr vehicle;
    pt::ptime beginTime;
    pt::ptime endTime=pt::not_a_date_time;
    unsigned int rentCost=0;
public:
    Rent(const boost::uuids::uuid &InitialID, ClientPtr Initial_client, VehiclePtr Initial_vehicle, const pt::ptime &InitialbeginTime);
    VehiclePtr getRentVehicle() const;
    ClientPtr getRentClient() const;
    std::string getRentInfo() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    void endRent(const pt::ptime &InitialendTime);
    unsigned int getRentDays() const;
    const unsigned int &getRentCost() const;
    std::string getInfo() const;
    const boost::uuids::uuid &getId() const;

};



#endif //CARRENTAL_RENT_H
