#ifndef CARRENTAL_RENTREPOSITORY_H
#define CARRENTAL_RENTREPOSITORY_H
#include "model/Rent.h"
#include "Repository.h"
class RentRepository : public Repository<Rent,RentException>{

};
bool allRentpredicate(const RentPtr ptr);
bool rentID1(const RentPtr ptr);

#endif //CARRENTAL_RENTREPOSITORY_H
