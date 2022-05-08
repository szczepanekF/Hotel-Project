#ifndef CARRENTAL_CLIENTREPOSITORY_H
#define CARRENTAL_CLIENTREPOSITORY_H
#include "model/Client.h"
#include <vector>



class ClientRepository {
private:
    std::vector<ClientPtr> ClientRepo;
public:
    ClientPtr get(const unsigned int &i) const;
    void add(ClientPtr client)  ;
    void remove(ClientPtr client);
    std::string report() const;
    unsigned int size() const;
    virtual ~ClientRepository();
    std::vector<ClientPtr> findBy(ClientPredicate predicate) const;
    std::vector<ClientPtr> findAll() const;
    ClientPtr findByPersonalID(const std::string &ID)const;

};
bool allClientpredicate(const ClientPtr ptr);
bool clientID1(const ClientPtr ptr);

#endif //CARRENTAL_CLIENTREPOSITORY_H
