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
    Client(const std::string &firtsName, const std::string &lastName, const std::string &personalId,
           const ClientTypePtr &clientType);
    virtual ~Client();
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getPersonalId() const;
    const ClientTypePtr &getClientType() const;
    bool isArchive() const;
    double getBill() const;
    void setFirstName(const std::string &firtsName);
    void setLastName(const std::string &lastName);
    void setClientType(const ClientTypePtr &clientType);
    void setArchive(bool archive);
    void setBill(double bill);
    int getMaxDays() const;
    bool acceptDiscount() const;
    std::string getInfo() const;

};


#endif //PROJECT_CLIENT_H
