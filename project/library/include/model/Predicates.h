#ifndef HOTELPROJECT_PREDICATES_H
#define HOTELPROJECT_PREDICATES_H
#include "typedefs.h"
#include <regex>
#include <boost/date_time.hpp>


class ClientLastNamePredicate { ///predykat który porównuje czy nazwisko klienta pasuje to podanego wzorca (może rozpoczynać się z małej litery)
private:
std::string spattern;
std::regex pattern;
public:
    explicit ClientLastNamePredicate(const std::string &initial_spattern);///rzuca wyjątek gdy wzorzec jest pusty, pierwsza litera jest zmieniana na wielką
    bool operator()(const ClientPtr &ptr) const ;
};

class RoomBasePricePredicate {///predykat sprawdzający czy cena za noc pokoju jest większa od podanej
private:
    double patternprice;
public:
    explicit RoomBasePricePredicate(double initial_patternprice);///rzuca wyjątek gdy wzorcowa cena jest mniejsza lub równa zero
    bool operator()(const RoomPtr &ptr) const ;

};

class ReservationBeginTimePredicate{/// predykat sprawdzający czy rezerwacja rozpoczęła się po wzorcowym czasie
private:
    boost::posix_time::ptime patternBeginTime;
public:
    explicit ReservationBeginTimePredicate(const boost::posix_time::ptime &initial_patternBeginTime);///rzuca wyjątek gdy wzorcowa data jest not_a_date_time
    bool operator()(const ReservationPtr &ptr) const ;

};


#endif //HOTELPROJECT_PREDICATES_H
