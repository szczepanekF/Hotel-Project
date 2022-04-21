//
// Created by student on 08.04.2022.
//

#ifndef CARRENTAL_CLIENTREPOSITORY_H
#define CARRENTAL_CLIENTREPOSITORY_H
#include "../model/Client.h"
#include <vector>
#include "typedefs.h"
#include <string>

class ClientRepository {
private:
    std::vector<ClientPtr> clientList;

public:

    ~ClientRepository();

    ClientPtr get_client(unsigned int i) const;

    void add_client(ClientPtr const new_Client);
    void remove_client(ClientPtr rm_Client);

    const std::string report_clientList() const;
    const unsigned int size_clientList() const;

    std::vector<ClientPtr> findBy(ClientPredicate predicate) const;
    std::vector<ClientPtr> findAll() const;
    ClientPtr findByPersonalId(const std::string &personalID) const;
};
#endif //CARRENTAL_CLIENTREPOSITORY_H
