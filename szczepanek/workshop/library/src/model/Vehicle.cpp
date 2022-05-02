
#include "model/Vehicle.h"


using namespace std;

Vehicle::Vehicle(const string &init_plateNumber, const unsigned int &init_basePrice)
    :plateNumber(init_plateNumber),basePrice(init_basePrice)
{

}

Vehicle::~Vehicle() {}

const string Vehicle::getVehicleInfo() const
{
    return "plate number: " + plateNumber + ", price: " + to_string(basePrice);
}


const string &Vehicle::get_plateNumber() const
{
    return plateNumber;
}
const unsigned int &Vehicle::get_basePrice() const
{
    return basePrice;
}
const bool &Vehicle::isArchive() const
{
    return archive;
}


void Vehicle::set_plateNumber(const string &new_plateNumber)
{
    if(new_plateNumber.compare("")!=0)
        plateNumber = new_plateNumber;
}
void Vehicle::set_basePrice(const unsigned int &new_basePrice)
{
    basePrice = new_basePrice;
}
void Vehicle::setArchive(bool const &new_archive)
{
    archive = new_archive;
}

double Vehicle::get_ActualRentalPrice() const
{
    return basePrice/1.0;
}