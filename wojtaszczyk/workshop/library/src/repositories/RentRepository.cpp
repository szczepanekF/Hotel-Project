#include "repositories/RentRepository.h"


bool allRentpredicate(const RentPtr ptr) {
    return true;
}

bool rentID1(const RentPtr ptr) {
    boost::uuids::uuid ID={2};
    return ptr->getId()==ID;
}
