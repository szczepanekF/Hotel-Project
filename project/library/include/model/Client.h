#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H
#include "typedefs.h"
#include <string>


class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    ClientTypePtr ClientType;
    bool archive;
    double bill;
public:
    Client(const std::string &initial_firtsName, const std::string &initial_lastName, const std::string &initial_personalId,
           const ClientTypePtr &initial_clientType);
    virtual ~Client();
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalId() const;
    const std::string &getId() const;
    const ClientTypePtr &getClientType() const;
    bool isArchive() const;
    double getBill() const;
    void setFirstName(const std::string &initial_firtsName);
    void setLastName(const std::string &initial_lastName);
    void setClientType(const ClientTypePtr &initial_clientType);
    void setArchive(bool initial_archive);
    void setBill(double initial_bill);
    int getMaxDays() const;
    bool acceptDiscount() const;
    std::string getInfo() const;

};


#endif //PROJECT_CLIENT_H
