#ifndef HOTELPROJECT_RESERVATIONREPOSITORY_H
#define HOTELPROJECT_RESERVATIONREPOSITORY_H
#include "repositories/Repository.h"


class Reservation;
class ReservationError;

class ReservationRepository: public Repository<Reservation,ReservationError>{
public:
    ReservationRepository();
    ~ReservationRepository() override;

};


#endif //HOTELPROJECT_RESERVATIONREPOSITORY_H
