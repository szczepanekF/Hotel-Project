
#include "model/Address.h"


using namespace std;
Address::Address(const std::string &Initialcity,const std::string &Initialstreet,const std::string &Initialnumber)
    :city(Initialcity), street(Initialstreet), number(Initialnumber){

}
string Address::GetAddressInfo() const{
    return city+ " "+street+" "+number;
}
const string &Address::GetAddresscity() const {
    return city;
}
const string &Address::GetAddressnumber() const{
    return number;
}
const string &Address::GetAddressstreet() const{
    return street;
}

