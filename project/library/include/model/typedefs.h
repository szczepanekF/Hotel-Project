#ifndef HOTELPROJECT_TYPEDEFS_H
#define HOTELPROJECT_TYPEDEFS_H
#include <memory>
#include <functional>
class Client;
class ClientType;
class Room;
class Reservation;
//class Repository;
class ClientRepository;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<Reservation> ReservationPtr;
//typedef std::shared_ptr<Repository> RepositoryPtr;
typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(RoomPtr)> RoomPredicate;
typedef std::function<bool(ReservationPtr)> ReservationPredicate;

#endif //HOTELPROJECT_TYPEDEFS_H
