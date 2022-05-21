
#include "repositories/ClientRepository.h"



bool allClientpredicate(const ClientPtr ptr) {
    return true;
}

bool clientID1(const ClientPtr ptr) {
    return ptr->getClientPersonalID()=="1";
}
