//
// Created by student on 08.04.2022.
//

#ifndef CARRENTAL_RENTREPOSITORY_H
#define CARRENTAL_RENTREPOSITORY_H
#include "../model/Rent.h"
#include <vector>
#include "typedefs.h"
#include <string>

class RentRepository {
private:
    std::vector<RentPtr> rentList;

public:

    ~RentRepository();

    RentPtr get_rent(unsigned int i) const;

    void add_rent(RentPtr const new_Rent);

    void remove_rent(RentPtr rm_Rent);
    const std::string report_rentList() const;

    const unsigned int size_rentList() const;

    std::vector<RentPtr> findBy(RentPredicate predicate) const;

    std::vector<RentPtr> findAll() const;
};
#endif //CARRENTAL_RENTREPOSITORY_H
