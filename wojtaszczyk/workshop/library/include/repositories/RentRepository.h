#ifndef CARRENTAL_RENTREPOSITORY_H
#define CARRENTAL_RENTREPOSITORY_H
#include "model/Rent.h"

class RentRepository {
private:
    std::vector<RentPtr> RentRepo;
public:
    RentPtr get(const unsigned int &i) const;
    void add(RentPtr rent);
    void remove(RentPtr rent);
    std::string report() const;
    unsigned int size() const;
    virtual ~RentRepository();
    std::vector<RentPtr> findBy(RentPredicate predicate) const;
    std::vector<RentPtr> findAll() const;
};
bool allRentpredicate(const RentPtr ptr);
bool rentID1(const RentPtr ptr);

#endif //CARRENTAL_RENTREPOSITORY_H
