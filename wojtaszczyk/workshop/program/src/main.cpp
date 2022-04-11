
#include "model/Client.h"
#include "model/Address.h"
#include "model/Vehicle.h"
#include "model/Rent.h"
#include <boost/date_time.hpp>
using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main()
{
    pt::ptime empty = pt::not_a_date_time;
//    cout << empty << endl;
//    pt::ptime now = pt::second_clock::local_time();
//    cout << now << endl;
//    pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25));
//    cout << then << endl;
//    pt::time_period period(then, now);
//    cout << period << endl;
//    cout << period.length() << endl;
//    cout << period.length().hours() << endl;
//    cout << period.length().minutes() << endl;
//    cout << (then>now) << endl;
//    cout << (then<=now) << endl;
//
//    // konwersja ptime na string z użyciem stringstream
//    std::stringstream ss;
//    ss << now;
//    string s = ss.str();
//    cout << s << endl;
    Vehicle v("12345", 23);
    Address a("Pabaincie","Dobra","25");
    Address*p=&a;
    Client c1("Miłosz","Wojtaszczyk","242567",p);
    Client c2("Jan","Kowalski","244456",p);
    string fname1 = "Jon";
    Client c(fname1, "Arbuckle", "0123456789",p);
    Rent r(1,&c,&v,empty);
    cout<<r.GetRentInfo()<<endl;
    cout<<r.GetRentClient()->GetClient_RentNumber()<<endl;
    Client *f=r.GetRentClient();
    unsigned int i=0;
    Rent *g=f->GetClientRent(i);
    cout<<g->GetRentInfo()<<endl;

    cout<<'\n'<<'\n';
    c.GetFullClientInfo();

    cout<<r.getRentDays()<<endl;


    return 0;
}
