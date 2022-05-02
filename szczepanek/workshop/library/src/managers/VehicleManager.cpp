#include "managers/VehicleManager.h"
#include "model/Bicycle.h"
#include "model/Moped.h"

using namespace std;

VehiclePtr VehicleManager::getVehicle(const std::string &plateNumber) const {
    return vehicleRepository.findByPlateNumber(plateNumber);
}

VehiclePtr VehicleManager::registerBicycle(const std::string &initPlateNumber, const unsigned int &initBasePrice) {
    VehiclePtr newvehicle;
    newvehicle = getVehicle(initPlateNumber);
    if(newvehicle != nullptr)
        return newvehicle;
    newvehicle = std::make_shared<Bicycle>(initPlateNumber,initBasePrice);
    vehicleRepository.add_vehicle(newvehicle);
    return newvehicle;
}

VehiclePtr VehicleManager::registerMoped(const std::string &initPlateNumber, const unsigned int &initBasePrice,
                                         const unsigned int &init_engineDisplacement) {
    VehiclePtr newvehicle;
    newvehicle = getVehicle(initPlateNumber);
    if(newvehicle != nullptr)
        return newvehicle;
    newvehicle = std::make_shared<Moped>(initPlateNumber,initBasePrice,init_engineDisplacement);
    vehicleRepository.add_vehicle(newvehicle);
    return newvehicle;
}

VehiclePtr VehicleManager::registerCar(const std::string &initPlateNumber, const unsigned int &initBasePrice,
                                       const unsigned int &init_engineDisplacement, const SegmentType &init_segment) {
    VehiclePtr newvehicle;
    newvehicle = getVehicle(initPlateNumber);
    if(newvehicle != nullptr)
        return newvehicle;
    newvehicle = std::make_shared<Car>(initPlateNumber,initBasePrice,init_engineDisplacement,init_segment);
    vehicleRepository.add_vehicle(newvehicle);
    return newvehicle;
}


void VehicleManager::unregisterVehicle(VehiclePtr vehicleptr)
{
    if(vehicleptr != nullptr && getVehicle(vehicleptr->get_plateNumber()) ==vehicleptr)
        vehicleptr->setArchive(true);
}

std::vector<VehiclePtr> VehicleManager::findVehicles(VehiclePredicate predicate) const
{

    VehiclePredicate archive= [predicate](VehiclePtr ptr)
    {
        return predicate(ptr) && ptr->isArchive()==false;
    };
    vector<VehiclePtr> found;
    for (unsigned int i = 0; i < vehicleRepository.size_vehicleList(); i++) {
        VehiclePtr vehicle = vehicleRepository.get_vehicle(i);
        if (vehicle != nullptr && archive(vehicle)) {
            found.push_back(vehicle);
        }
    }
    return found;
}
