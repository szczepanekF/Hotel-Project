
#include "model/Address.h"


using namespace std;
Address::Address(const std::string &Initialcity,const std::string &Initialstreet,const std::string &Initialnumber)
    :city(Initialcity), street(Initialstreet), number(Initialnumber){

}
string Address::getAddressInfo() const{
    return city+ " "+street+" "+number;
}
const string &Address::getAddresscity() const {
    return city;
}
const string &Address::getAddressnumber() const{
    return number;
}
const string &Address::getAddressstreet() const{
    return street;
}

