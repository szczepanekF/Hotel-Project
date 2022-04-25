#include "repositories/VehicleRepository.h"


VehiclePtr VehicleRepository::get(const unsigned int &i) const {
    if (i<=this->size() && i>=0){
        return VehicleRepo[i];}
    else
        return nullptr;
}

void VehicleRepository::add(VehiclePtr vehicle) {
    if(vehicle!= nullptr){
        VehicleRepo.push_back(vehicle);
    }
}

void VehicleRepository::remove(VehiclePtr vehicle) {
    VehicleRepo.erase(std::remove(VehicleRepo.begin(),VehicleRepo.end(),vehicle),VehicleRepo.end());
    delete vehicle;
}

std::string VehicleRepository::report() const {
    std::stringstream ss;
    unsigned int x=this->size();
    for (int i=0;i<x;i++)
    {
        ss << this->get(i)->getVehicleInfo() << '\n';
    }
    return ss.str();
}

unsigned int VehicleRepository::size() const {
    return VehicleRepo.size();
}

VehicleRepository::~VehicleRepository() {
    for(int i=0;i<size();i++)
    {
        VehiclePtr v=get(i);
        delete v;
    }

}

std::vector<VehiclePtr> VehicleRepository::findBy(VehiclePredicate predicate) const {
    std::vector<VehiclePtr> found;
    for (unsigned int i = 0; i < VehicleRepo.size(); i++) {
        VehiclePtr vehicle = get(i);
        if (vehicle != nullptr && predicate(vehicle)) {
            found.push_back(vehicle);
        }
    }
    return found;
}

std::vector<VehiclePtr> VehicleRepository::findAll() const {
    return findBy(allVehiclepredicate);
}

bool allVehiclepredicate(const VehiclePtr ptr) {
    return true;
}

bool vehiclebaseprice25(const VehiclePtr ptr) {
    return ptr->getVehiclebasePrice()==25;
}
