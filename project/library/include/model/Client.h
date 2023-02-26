#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H
#include "typedefs.h"
#include <string>


class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    ClientTypePtr ClientType; ///typ klienta określa czy jest dopuszczony do zniżki i ile dni może trwać pojedyńcza rezerwacja (short_term, Standard i LongTerm)
    bool archive;
    double balance; ///stan konta klienta, który jest zmniejszany podczas tworzenia nowej rezerwacji
public:
    Client(const std::string &initial_firtsName, const std::string &initial_lastName, const std::string &initial_personalId,
           const ClientTypePtr &initial_clientType); ///rzuca wyjątek, gdy: którekolwiek z pól firstName,lastName lub personalID bęðzie puste lub clientType==nullptr
    virtual ~Client();

    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getId() const;///zwraca personalID
    const ClientTypePtr &getClientType() const;
    bool isArchive() const;
    double getBalance() const;

    void setFirstName(const std::string &new_firstName);///rzuca wyjątek w trakcie próby zmiany na puste pole
    void setLastName(const std::string &new_lastName);///rzuca wyjątek w trakcie próby zmiany na puste pole
    void setClientType(const ClientTypePtr &new_clientType);///rzuca wyjątek w trakcie próby zmiany na puste pole
    void setArchive(bool new_archive);
    void setBalance(double new_bill);

    unsigned int getMaxDays() const; ///zwraca maksymalną ilość dni jaką może spędzkić klient w czasie jednej rezerwacji
    bool acceptDiscount() const; ///określa czy klient kwalifikuje się do zniżki
    std::string getInfo() const;
    std::string toDBInfo() const;
};


#endif //PROJECT_CLIENT_H
