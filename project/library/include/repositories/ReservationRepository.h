//
// Created by student on 30.05.2022.
//

#ifndef HOTELPROJECT_RESERVATIONREPOSITORY_H
#define HOTELPROJECT_RESERVATIONREPOSITORY_H
#include "repositories/Repository.h"
#include "exceptions/ReservationError.h"

class Reservation;
class ReservationRepository: public Repository<Reservation,ReservationError>{
public:
    ReservationRepository();
    ~ReservationRepository() override;

};


#endif //HOTELPROJECT_RESERVATIONREPOSITORY_H
