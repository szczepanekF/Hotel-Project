#include "managers/VehicleManager.h"

VehiclePtr VehicleManager::getVehicle(const std::string &Plate) const {
    return currentVehicles->findByPlate(Plate);
}

VehiclePtr VehicleManager::registerMoped(const std::string &Initial_Plate, const unsigned int &BasePrice,
                                       const unsigned int &engine) {
    if(getVehicle(Initial_Plate)!= nullptr)
    {
        return getVehicle(Initial_Plate);
    }
    else{
        MopedPtr vehicle= std::make_shared<Moped>(Initial_Plate,BasePrice,engine);
        currentVehicles->add(vehicle);
        return vehicle;
    }
}

VehiclePtr VehicleManager::registerBicycle(const std::string &Initial_Plate, const unsigned int &BasePrice) {
    if(getVehicle(Initial_Plate)!= nullptr)
    {
        return getVehicle(Initial_Plate);
    }
    else{
        VehiclePtr vehicle= std::make_shared<Bicycle>(Initial_Plate,BasePrice);
        currentVehicles->add(vehicle);
        return vehicle;
    }
}

VehiclePtr VehicleManager::registerCar(const std::string &Initial_Plate, const unsigned int &BasePrice, const unsigned int &engine,
                            SegmentType segment) {
    if(getVehicle(Initial_Plate)!= nullptr)
    {
        return getVehicle(Initial_Plate);
    }
    else{
        VehiclePtr vehicle= std::make_shared<Car>(Initial_Plate,BasePrice,engine,segment);
        currentVehicles->add(vehicle);
        return vehicle;
    };
}

std::vector<VehiclePtr> VehicleManager::findVehicles(VehiclePredicate predicate) const {
    VehiclePredicate f =[predicate](VehiclePtr ptr)->bool{return predicate(ptr) ;};
    return currentVehicles->findBy(f);
}

std::vector<VehiclePtr> VehicleManager::findAllVehicles() const {
    VehiclePredicate f =[](VehiclePtr ptr)->bool{return true ;};
    return currentVehicles->findBy(f);
}

VehicleManager::VehicleManager() {
    currentVehicles = std::make_shared<VehicleRepository>();
}
