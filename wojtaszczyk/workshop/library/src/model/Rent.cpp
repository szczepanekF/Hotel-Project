#include "model/Rent.h"
#include "model/Vehicle.h"
#include "model/Client.h"

Rent::Rent(const boost::uuids::uuid &InitialID, ClientPtr Initial_client, VehiclePtr Initial_vehicle, const pt::ptime &InitialbeginTime)
try:id(InitialID),client(Initial_client),vehicle(Initial_vehicle){


    if(InitialbeginTime==pt::not_a_date_time){
        beginTime=pt::second_clock::local_time();
    }
    else{
        beginTime=InitialbeginTime;
    }
    if(boost::uuids::to_string(InitialID).empty()){
        throw RentException("Bad ID Error");
    }
    if(Initial_client==nullptr){
        throw RentException("null Client Error");
    }
    if(Initial_vehicle==nullptr){
        throw RentException("null Vehicle Error");
    }
}catch(const RentException &e){
    std::cout<<e.what()<<'\n';
}

std::string Rent::getRentInfo() const {
    std::stringstream ss;
    ss <<beginTime<<" "<<endTime;
    return boost::uuids::to_string(id) + " " + client->getClientInfo() + " " + vehicle->getVehicleInfo() + " " + ss.str();
}


ClientPtr Rent::getRentClient() const {
    return client;
}

VehiclePtr Rent::getRentVehicle() const {
    return vehicle;
}

const pt::ptime &Rent::getBeginTime() const {
    return beginTime;
}

const pt::ptime &Rent::getEndTime() const {
    return endTime;
}

void Rent::endRent(const pt::ptime &InitialendTime) {
    if(endTime==pt::not_a_date_time)
    {
        if(InitialendTime==pt::not_a_date_time)
        {
            endTime=pt::second_clock::local_time();
        }
        else if(InitialendTime<beginTime)
        {
            endTime=beginTime;
        }
        else
        {
            endTime=InitialendTime;
        }
        rentCost= vehicle->getVehiclebasePrice() * getRentDays();
        rentCost=rentCost-client->applyDiscount(rentCost);
    }


}

 unsigned int Rent::getRentDays() const {


    if(endTime==pt::not_a_date_time)
    {

        return 0;
    }
    else
    {
        pt::time_period period(beginTime,endTime);
        if (period.length().hours() == 0 && period.length().minutes() == 0) {

            return 0;
        }
        else{

            return period.length().hours()/24+1;

        }
    }

}
const unsigned int &Rent::getRentCost() const {
    return rentCost;
}

std::string Rent::getInfo() const {
    return getRentInfo();
}

const boost::uuids::uuid &Rent::getId() const {
    return id;
}
