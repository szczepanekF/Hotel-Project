#include "repositories/VehicleRepository.h"
#include "repositories/RentRepository.h"

using namespace std;

VehicleRepository::~VehicleRepository()
{
    for(int i = 0;i<vehicleList.size();i++)
    {
        VehiclePtr veh=vehicleList[i];
//        delete veh;
    }
}

VehiclePtr VehicleRepository::get_vehicle(unsigned int i) const
{
    if(i<size_vehicleList())
        return vehicleList[i];
    return nullptr;
}

void VehicleRepository::add_vehicle(const VehiclePtr new_Vehicle)
{
    if(new_Vehicle != nullptr)
        vehicleList.push_back(new_Vehicle);
}

void VehicleRepository::remove_vehicle(VehiclePtr rm_Vehicle)
{
    if(rm_Vehicle != nullptr)
    {
        vehicleList.erase(remove(vehicleList.begin(),vehicleList.end(),rm_Vehicle),vehicleList.end());
//        delete rm_Vehicle;
    }
}

const std::string VehicleRepository::report_vehicleList() const
{
    stringstream ss;


    for(int i = 0; i < size_vehicleList(); i++)
        ss<<vehicleList[i]->getVehicleInfo() << "\n";
    string s = ss.str();
    return s;
}

const unsigned int VehicleRepository::size_vehicleList() const
{
    return vehicleList.size();
}

std::vector<VehiclePtr> VehicleRepository::findBy(VehiclePredicate predicate) const
{
    vector<VehiclePtr> found;
    for (unsigned int i = 0; i < size_vehicleList(); i++) {
        VehiclePtr vehicle = get_vehicle(i);
        if (vehicle != nullptr && predicate(vehicle)) {
            found.push_back(vehicle);
        }
    }
    return found;
}
bool testtrue1(const VehiclePtr ptr)
{
    return true;
}

std::vector<VehiclePtr> VehicleRepository::findAll() const
{
    return findBy(testtrue1);
}

VehiclePtr VehicleRepository::findByPlateNumber(const std::string &plateNumber) const
{
    VehiclePredicate vehiclePlatenumber = [plateNumber](VehiclePtr ptr)
    {
        return ptr->get_plateNumber()==plateNumber;
    };
    vector<VehiclePtr> found = findBy(vehiclePlatenumber);

    if(found.size()==0)
        return nullptr;
    return found[0];
}