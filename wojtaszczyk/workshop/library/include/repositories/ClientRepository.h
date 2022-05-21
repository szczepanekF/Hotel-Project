#ifndef CARRENTAL_CLIENTREPOSITORY_H
#define CARRENTAL_CLIENTREPOSITORY_H
#include "model/Client.h"
#include <vector>
#include "Repository.h"


class ClientRepository:public Repository<Client,ClientException> {
//public:
//    template<class P> std::vector<ClientPtr> find(const P &predicate) const
//    {
//        std::vector<ClientPtr> result;
//        for(int i = 0; i<size(); ++i)
//        {
//            ClientPtr rent = objects[i];
//            if(predicate(rent))
//            {
//                result.push_back(rent);
//            }
//        }
//        return result;
//    }
};
bool allClientpredicate(const ClientPtr ptr);
bool clientID1(const ClientPtr ptr);

#endif //CARRENTAL_CLIENTREPOSITORY_H
