#include "model/Rent.h"
#include "model/Vehicle.h"
#include "model/Client.h"

Rent::Rent(const unsigned int &InitialID,Client *Initial_client,Vehicle *Initial_vehicle,const pt::ptime &InitialbeginTime)
:id(InitialID),client(Initial_client),vehicle(Initial_vehicle){
    client->AddNewRent(this);
    vehicle->setRetend(true);
    if(InitialbeginTime==pt::not_a_date_time){
        beginTime=pt::second_clock::local_time();
    }
    else{
        beginTime=InitialbeginTime;
    }
}
std::string Rent::GetRentInfo() const {
    std::stringstream ss;
    ss <<beginTime<<" "<<endTime;
    return std::to_string(id)+ " "+client->GetClientInfo()+" "+vehicle->GetVehicleInfo()+" "+ss.str();
}
const unsigned int &Rent::GetRentID() const {
    return id;
}

Client *Rent::GetRentClient() const {
    return client;
}

Vehicle *Rent::GetRentVehicle() const {
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
        vehicle->setRetend(false);
        client->removeClientRent(this);
        rentCost=vehicle->GetVehiclebasePrice()*this->getRentDays();

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
unsigned int Rent::getRentCost() const {
    return rentCost;
}