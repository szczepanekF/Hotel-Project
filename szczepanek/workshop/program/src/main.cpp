#include <iostream>

#include "model/Client.h"

using namespace std;

int main()
{
    Address b("a","B","c");
    string fname1 = "Jon";
    Client c(fname1, "Arbuckle", "0123456789",&b);
    Vehicle veh("232322", 5005);
    Rent rent(1,&c,&veh,pt::second_clock::local_time()-pt::minutes(50));
    rent.endRent();
    //cout<<c.get_rentNumber();
    cout<<pt::minutes(50);

;

    //cout<<rent.getRentInfo()<<'\n';
    //c.getFullClientInfo();







    return 0;
}
