#ifndef HOTELPROJECT_TYPEDEFS_H
#define HOTELPROJECT_TYPEDEFS_H
#include <memory>
#include <functional>
class Client;
class ClientType;
class Room;
class Reservation;

class ClientRepository;
class RoomRepository;
class ReservationRepository;

class ClientManager;
class RoomManager;
class ReservationManager;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<Reservation> ReservationPtr;

typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::shared_ptr<RoomRepository> RoomRepositoryPtr;
typedef std::shared_ptr<ReservationRepository> ReservationRepositoryPtr;


typedef std::shared_ptr<ClientManager> ClientManagerPtr;
typedef std::shared_ptr<RoomManager> RoomManagerPtr;
typedef std::shared_ptr<ReservationManager> ReservationManagerPtr;


typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(RoomPtr)> RoomPredicate;
typedef std::function<bool(ReservationPtr)> ReservationPredicate;

#endif //HOTELPROJECT_TYPEDEFS_H
