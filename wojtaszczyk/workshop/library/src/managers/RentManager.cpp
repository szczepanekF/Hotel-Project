#include "managers/RentManager.h"

std::vector<RentPtr> RentManager::findAllClientRents(const ClientPtr &ptr) const {
    RentPredicate f=[ptr](const RentPtr& ptr2)->bool{return ptr==ptr2->getRentClient();};
    return currentRents->findBy(f);
}

RentPtr RentManager::findVehicleRent(const VehiclePtr &ptr) const {
    for (unsigned int i = 0; i < currentRents->size(); i++) {
        RentPtr rent = currentRents->get(i);
        if (rent != nullptr && rent->getRentVehicle()==ptr) {
            return rent;
        }
    }
    return nullptr;
}

std::vector<RentPtr> RentManager::findRents(RentPredicate predicate) const {
    return currentRents->findBy(predicate);
}

std::vector<RentPtr> RentManager::findAllRents() const {
    return currentRents->findAll();
}

double RentManager::checkClientRentBalance(const ClientPtr &ptr) const {
    RentPredicate f=[ptr](const RentPtr& ptr2)->bool{return ptr==ptr2->getRentClient();};
    std::vector<RentPtr> all= archiveRents->findBy(f);
    double s=0;
    for(int i=0;i<all.size();i++)
    {
        s=s+all[i]->getRentCost();
    }
    return s;
}

RentPtr RentManager::rentVehicle(const ClientPtr &cptr, const VehiclePtr &vptr,const pt::ptime &InitialbeginTime) {
    if(!cptr->isArchive() && findAllClientRents(cptr).size()< cptr->getMaxVehicles() && findVehicleRent(vptr) == nullptr){
        boost::uuids::uuid ID=boost::uuids::random_generator()();
        while(currentRents->findBy([ID](const RentPtr &ptr)->bool{return ptr->getId()==ID;}).size()!=0 && archiveRents->findBy([ID](const RentPtr &ptr)->bool{return ptr->getId()==ID;}).size()!=0){
            ID=boost::uuids::random_generator()();
        }
        RentPtr rent=std::make_shared<Rent>(ID,cptr,vptr,InitialbeginTime);
        currentRents->add(rent);
        return rent;
    }
    else{
       if(cptr->isArchive()){
           throw ClientException("Archive Error");
       }
       else if(!(findAllClientRents(cptr).size()< cptr->getMaxVehicles())){
           throw ClientException("Too many cars Error");
       }
       else if(findVehicleRent(vptr) != nullptr){
           throw RentException("Vehicle Already Taken Error");
       }
       return nullptr;
    }
}

void RentManager::returnVehicle(const VehiclePtr &vptr) {
    if((findVehicleRent(vptr)!= nullptr)){
        RentPtr rent=findVehicleRent(vptr);
        rent->endRent(pt::not_a_date_time);
        currentRents->remove(rent);
        archiveRents->add(rent);
    }else
        throw RentException("no Vehicle Error");
}

void RentManager::changeClientType(const ClientPtr &ptr) {
    if(ptr== nullptr){
        throw RentException("null Argument Error");
    }
    double s= checkClientRentBalance(ptr);
    ClientTypePtr type;
    if(s>=0&&s<100){
        type=std::make_shared<Default>();
    }
    else if(s<200){
        type=std::make_shared<Bronze>();
    }
    else if(s<400){
        type=std::make_shared<Silver>();
    }
    else if(s<800){
        type=std::make_shared<Gold>();
    }
    else if(s<1600){
        type=std::make_shared<Platinum>();
    }
    else {
        type=std::make_shared<Diamond>();
    }
    ptr->setClientType(type);
}

RentManager::RentManager() {
    currentRents= std::make_shared<RentRepository>();
    archiveRents= std::make_shared<RentRepository>();
}
