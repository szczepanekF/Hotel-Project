#include "repositories/RentRepository.h"

using namespace std;

RentRepository::~RentRepository()
{
    for(int i = 0;i<rentList.size();i++)
    {
        RentPtr ren=rentList[i];
//        delete ren;
    }
}

RentPtr RentRepository::get_rent(unsigned int i) const
{
    if(i<size_rentList())
        return rentList[i];
    return nullptr;
}

void RentRepository::add_rent(const RentPtr new_Rent)
{
    if(new_Rent != nullptr)
        rentList.push_back(new_Rent);
}

void RentRepository::remove_rent(RentPtr rm_Rent)
{
    if(rm_Rent != nullptr)
    {
        rentList.erase(remove(rentList.begin(),rentList.end(),rm_Rent),rentList.end());
//        delete rm_Rent;
    }

}

const std::string RentRepository::report_rentList() const
{
    stringstream ss;
    for(int i = 0; i<size_rentList();i++)
        ss<<rentList[i]->getRentInfo() <<'\n';
    string s = ss.str();
    return s;
}

const unsigned int RentRepository::size_rentList() const
{
    return rentList.size();
}

std::vector<RentPtr> RentRepository::findBy(RentPredicate predicate) const
{
    vector<RentPtr> found;
    for (unsigned int i = 0; i < size_rentList(); i++) {
        RentPtr rent = get_rent(i);
        if (rent != nullptr && predicate(rent)) {
            found.push_back(rent);
        }
    }
    return found;
}

bool testtrue1(const RentPtr ptr)
{
    return true;
}
std::vector<RentPtr> RentRepository::findAll() const
{
    return findBy(testtrue1);
}