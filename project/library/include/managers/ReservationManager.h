#ifndef HOTELPROJECT_RESERVATIONMANAGER_H
#define HOTELPROJECT_RESERVATIONMANAGER_H
#include "model/Reservation.h"
#include <vector>
class C_client;



class ReservationManager {
private:
    ReservationRepositoryPtr currentReservations;
    ReservationRepositoryPtr archiveReservations;
    bool reading = false;



public:
    ReservationManager(const ReservationRepositoryPtr &initial_currentReservations, const ReservationRepositoryPtr &initial_archiveReservations);
    virtual ~ReservationManager();

    ReservationPtr startReservation(const ClientPtr &client, const RoomPtr &room, unsigned int guestCount,
                                    const pt::ptime &beginTime, unsigned int reservationDays, extraBonusType bonus);

    ///przyjmuje wartości potrzebne do utowrzenia obiektu rezerwacji, rzuca wyjątek gdy klient jest archiwalny, pokój jest zajęty, czas rozpoczęcia rezerwacji jest mniejszy od obecnego czasu,
    ///ilość gości jest mniejsza od ilości łózek, ilość dni jest wieksza od maksymalnej ilości dni dla danego klienta,
    ///losuje unikatowe ID dla rezerwacji, tworzy obiekt rezerwacji, dodaje go do repozytorium,
    ///ustala jego początkowy koszt zależny od rachunku klienta i ceny za pokój, bonusu oraz ilości dni, jeżeli cena wyjdzie ujemna rezerwacja staje się darmowa (cena równa 0),
    ///zerowany jest rachunek klienta, zwracany jest wskaźnik na stworzony obiekt rezerwacji
    ReservationPtr readReservation(const ClientPtr &client, const RoomPtr &room, unsigned int guestCount,
                                   const pt::ptime &beginTime, unsigned int reservationDays, extraBonusType bonus);
    void endReservation(const ud::uuid &id);
    ///kończy podaną rezerwację, jeżeki typ klienta pozwala na przyznanie zniżki to jest ona naliczana do jego rachunku w zalezności o iloścni dni dotąd spędzonych w hotelu,
    ///usuwa obiekt rezerwacji z repozytorium obecnych wypożyczeń i dodaje go do repozytorium wypożyczeń archiwalnych
    void setReservationArchive(const ud::uuid &id);
    std::vector<ReservationPtr> findReservations(const ReservationPredicate &predicate) const; ///dotyczy obecnych wypożyczeń
    std::vector<ReservationPtr> findAllReservations() const;///dotyczy obecnych wypożyczeń
    std::vector<ReservationPtr> findClientReservations(const ClientPtr &client) const;///dotyczy obecnych wypożyczeń
    std::vector<ReservationPtr>  findRoomReservations(const RoomPtr &room) const;///dotyczy obecnych wypożyczeń
    void removeReservation(const ud::uuid &id);
    bool isRoomOccupied(const RoomPtr& room,const pt::ptime &beginTime,unsigned int resDays);

    double calculateDiscount(const ClientPtr &client) const;///określa wartosć procentową zniżki
    void changeReservationExtraBonusToB(const ud::uuid &id);



    ///zmienia bonuxy rezerwacji, w zależności od tego kiedy zachodzi zmiana (w trakcie lub przed rozpoczęceim rezerwacji) zmieniana jest cena rezerwacji,
    /// rzuca wyjątek przy próbie zmiany bonusu na mniejszy
    void changeReservationExtraBonusToC(const ud::uuid &id);
    double calculatePriceDifferenceAfterChange(const ud::uuid &id,extraBonusType new_Type);
    ///zmienia bonuxy rezerwacji, w zależności od tego kiedy zachodzi zmiana (w trakcie lub przed rozpoczęceim rezerwacji) zmieniana jest cena rezerwacji.
    void readReservationsFromServer(C_client* conn,ClientManagerPtr clients,RoomManagerPtr rooms);
    void addReservationToDB(C_client* conn,std::string &infos);
    void removeFromDB(C_client* conn,std::string &infos);
    void updateExtraBonusToDB(C_client* conn,const ReservationPtr &ptr);
};


#endif //HOTELPROJECT_RESERVATIONMANAGER_H
