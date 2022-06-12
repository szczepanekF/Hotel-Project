#ifndef HOTELPROJECT_CLIENTMANAGER_H
#define HOTELPROJECT_CLIENTMANAGER_H

#include "model/typedefs.h"
#include <vector>

class ClientRepository;

class ClientManager {
private:
    ClientRepositoryPtr clients;
public:
    explicit ClientManager(const ClientRepositoryPtr &initial_clients);
    virtual ~ClientManager();

    ClientPtr regiterClient(const std::string &initial_firstName, const std::string &initial_lastName, const std::string &initial_personalID, const ClientTypePtr &initial_clientType);
    ///przyjmuje wartości potrzebne do utworzenia obiektu klienta, sprawdza czy w repozytorium jest już klient o podanym personalID, jeżeli tak, rzuca wyjątek,
    ///w przeciwnym wypadku tworzony jest obiekt klienta, ustawiany jest dla niego odpowiedni rachunek zależny od typu oraz dodawany jest on do repozytorium
    ///zwraca wskaźnik na utworzony obiekt
    void unregisterClient(const std::string &personalID) const;///ustawia znacznik klienta określający, że jest on archiwalny
    ClientPtr getClient(const std::string &personalID) const;
    std::vector<ClientPtr> findClients(const ClientPredicate &predicate) const;
    std::vector<ClientPtr> findAllClients() const;
    void changeClientTypetoStandard(const std::string &personalID) const;///zmienia typ klienta, oraz zwiększa jego rachunek, rzuca wyjątek przy próbie zmiany na mniejszy lub ten sam typ
    void changeClientTypetoLongTerm(const std::string &personalID) const;///zmienia typ klienta, oraz zwiększa jego rachunek, rzuca wyjątek przy próbie zmiany na mniejszy lub ten sam typ

};


#endif //HOTELPROJECT_CLIENTMANAGER_H
