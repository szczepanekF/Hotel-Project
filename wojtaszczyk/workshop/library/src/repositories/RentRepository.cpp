#include "repositories/RentRepository.h"

RentPtr RentRepository::get(const unsigned int &i) const {
    if (i<this->size() && i>=0){
        return RentRepo[i];}
    else
        return nullptr;
}

void RentRepository::add(RentPtr rent) {
    if(rent!= nullptr){
        RentRepo.push_back(rent);
    }
}

void RentRepository::remove(RentPtr rent) {
    RentRepo.erase(std::remove(RentRepo.begin(),RentRepo.end(),rent),RentRepo.end());

}

std::string RentRepository::report() const {
    std::stringstream ss;
    unsigned int x=this->size();
    for (int i=0;i<x;i++)
    {
        ss << this->get(i)->getRentInfo() << '\n';
    }
    return ss.str();
}

unsigned int RentRepository::size() const {
    return RentRepo.size();
}

RentRepository::~RentRepository() {

}

std::vector<RentPtr> RentRepository::findBy(RentPredicate predicate) const {
    std::vector<RentPtr> found;
    for (unsigned int i = 0; i < RentRepo.size(); i++) {
        RentPtr rent = get(i);
        if (rent != nullptr && predicate(rent)) {
            found.push_back(rent);
        }
    }
    return found;
}

std::vector<RentPtr> RentRepository::findAll() const {
    return findBy(allRentpredicate);
}

bool allRentpredicate(const RentPtr ptr) {
    return true;
}

bool rentID1(const RentPtr ptr) {
    return ptr->getRentID()==2;
}
