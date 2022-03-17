//
// Created by student on 17.03.2022.
//

#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H
#include <string>

class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PersonalID;
    Client();
public:
    std::string GetClientInfo();
    Client(std::string Initial_FirstName, std::string Initial_LastName, std::string Initial_PersonalID);
    ~Client();
    std::string GetClientFirstName();
    std::string GetClientLastName();
    std::string GetClientPersonalID();
    void SetClientFirstName(std::string Changed_FirstName);
    void SetClientLastName(std::string Changed_LastName);



};


#endif //CARRENTAL_CLIENT_H
