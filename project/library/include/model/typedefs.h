#ifndef HOTELPROJECT_TYPEDEFS_H
#define HOTELPROJECT_TYPEDEFS_H
#include <memory>
class Client;
class ClientType;
class Room;
class Reservation;
//class Repository;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<Reservation> ReservationPtr;
//typedef std::shared_ptr<Repository> RepositoryPtr;


#endif //HOTELPROJECT_TYPEDEFS_H
