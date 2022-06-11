//
// Created by student on 06.06.2022.
//

#ifndef HOTELPROJECT_RESERVATIONMANAGER_H
#define HOTELPROJECT_RESERVATIONMANAGER_H
#include "model/Reservation.h"
#include <vector>
//#include "repositories/ReservationRepository.h"
//#include <boost/date_time.hpp>
//#include <boost/uuid/uuid.hpp>
//#include "model/typedefs.h"
//namespace pt = boost::posix_time;
//namespace ud = boost::uuids;

class ReservationManager {
private:
    ReservationRepositoryPtr currentReservations;
    ReservationRepositoryPtr archiveReservations;
public:
    ReservationManager(const ReservationRepositoryPtr &initial_currentReservations, const ReservationRepositoryPtr &initial_archiveReservations);
    ReservationManager();
    virtual ~ReservationManager();

    ReservationPtr startReservation(const ClientPtr &client,const RoomPtr &room,unsigned int guestCount,
                                    const ud::uuid id,const pt::ptime beginTime,unsigned int reservationDays,
                                    extraBonusType bonus);
    void endReservation(const ud::uuid id);
    std::vector<ReservationPtr> findReservations(ReservationPredicate predicate) const;
    std::vector<ReservationPtr> findAllReservations() const;
    std::vector<ReservationPtr> findClientReservations(const ClientPtr &client) const;
    ReservationPtr findRoomReservation(const RoomPtr &room) const;
    double calculateDiscount(const ClientPtr &client) const;
    void changeReservationExtraBonusToA(const ud::uuid id);
    void changeReservationExtraBonusToB(const ud::uuid id);
    void changeReservationExtraBonusToC(const ud::uuid id);
    void changeReservationExtraBonusToD(const ud::uuid id);
    void changeReservationExtraBonusToE(const ud::uuid id);
    void calculateTotalReservationPrice();

};


#endif //HOTELPROJECT_RESERVATIONMANAGER_H
