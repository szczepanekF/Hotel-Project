#include "managers/RentManager.h"
#include <memory>
#include <vector>
#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"


using namespace std;

std::vector<RentPtr> RentManager::getAllClientRents(ClientPtr client) const {
    return currentRents.findBy([client](RentPtr ptr){return ptr->get_client()==client;});
}


RentPtr RentManager::getVehicleRent(VehiclePtr vehicle) const {
//    vector<RentPtr> found=currentRents.findBy([vehicle](RentPtr ptr){return ptr->get_vehicle()==vehicle;});
//    if(found.size() == 0)
//        return nullptr;
//    return found[0];
    return currentRents.getVehicleRent(vehicle);
}

std::vector<RentPtr> RentManager::findRents(RentPredicate predicate) const {
    return currentRents.findBy(predicate);
}

std::vector<RentPtr> RentManager::findAllRents() const {
    return currentRents.findAll();
}

unsigned int RentManager::checkClientRentBalance(ClientPtr client) const
{
    unsigned int Balance= 0 ;

//    RentPredicate rentClient = [client](RentPtr ptr)
//    {
//        return ptr->get_client()==client;
//    };
    vector<RentPtr> found;
    found = archiveRents.findBy([client](RentPtr ptr){return ptr->get_client()==client;});
    for(int i=0; i < found.size(); i++)
    {
        Balance += found[i]->get_rentCost();
    }

    return Balance;

}

RentPtr RentManager::rentVehicle(const unsigned int &init_id, ClientPtr init_client, VehiclePtr init_vehicle,
                                 pt::ptime init_beginTime) {
    if(init_client == nullptr || init_vehicle == nullptr) return nullptr;
    if(init_client->isArchive() || init_vehicle->isArchive())
        return nullptr;
    if(getAllClientRents(init_client).size() >= init_client->getMaxVehicles())
        return nullptr;
    if(getVehicleRent(init_vehicle) != nullptr)
        return nullptr;

    RentPtr newrent;
    newrent = std::make_shared<Rent>(init_id,init_client,init_vehicle,init_beginTime);
    currentRents.add_rent(newrent);
    return newrent;
}

void RentManager::returnVehicle(VehiclePtr vehicle)
{
    RentPtr rent = getVehicleRent(vehicle);
    if(rent == nullptr)
        return;
    rent->endRent();

    archiveRents.add_rent(rent);
    currentRents.remove_rent(rent);
}

void RentManager::changeClientType(ClientPtr client)
{
    if(client == nullptr) return;
    double balance = checkClientRentBalance(client);
    ClientTypePtr type;
    if(balance >=0 && balance <100){
        type = std::make_shared<Default>();
    }else if(balance < 200)
        type = std::make_shared<Bronze>();
    else if(balance < 400)
        type = std::make_shared<Silver>();
    else if(balance < 800)
        type = std::make_shared<Gold>();
    else if(balance < 1600)
        type = std::make_shared<Platinum>();
    else
        type = std::make_shared<Diamond>();

    client->set_clientType(type);
}