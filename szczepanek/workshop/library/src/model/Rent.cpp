#include "model/Rent.h"


using namespace std;
namespace pt = boost::posix_time;

Rent::Rent(const unsigned int &init_id,ClientPtr init_client,VehiclePtr init_vehicle,pt::ptime init_beginTime)
    :id(init_id), client(init_client), vehicle(init_vehicle)
{
//    client->AddRent(this);
//    vehicle->set_rented(true);
    if(init_beginTime == pt::not_a_date_time)
        beginTime = pt::second_clock::local_time();
    else
        beginTime = init_beginTime;
}

const string Rent::getRentInfo() const
{
    stringstream ss;
    ss<<"RENT- ID: "+to_string(id) + " " + client->getClientInfo() + " " +
        vehicle->getVehicleInfo() + " Time: " ;
    ss << beginTime <<" -- "<<endTime;
    string s = ss.str();
    return s;
}

const unsigned int &Rent::get_id() const
{
    return id;
}

const ClientPtr Rent::get_client() const
{
    return client;
}

const VehiclePtr Rent::get_vehicle() const
{
    return vehicle;
}

const pt::ptime &Rent::get_beginTime() const
{
    return beginTime;
}
const pt::ptime &Rent::get_endTime() const
{
    return endTime;
}

const unsigned int &Rent::get_rentCost() const
{
    return rentCost;
}

unsigned int Rent::get_rentDays() const
{

    if(endTime == pt::not_a_date_time)
        return 0;
    pt::time_period period(beginTime,endTime);
    if(endTime-beginTime<=pt::seconds(59))
        return 0;
    else
        return period.length().hours()/24 + 1;
}



void Rent::endRent(pt::ptime new_endTime)
{
    if(endTime==pt::not_a_date_time){
        if(new_endTime == pt::not_a_date_time)
        {
            endTime = pt::second_clock::local_time();
        }
        else{
            if(beginTime > new_endTime)
                endTime = beginTime;
            else
                endTime = new_endTime;
        }
//        vehicle->set_rented(false);

//        client->remove_currentRent(this);
            rentCost=( get_rentDays() * vehicle->get_ActualRentalPrice()) - client->applyDiscount(get_rentDays()*vehicle->get_ActualRentalPrice());
//        vehicle->set_archive(true);
    }

}
