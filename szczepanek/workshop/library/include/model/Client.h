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
    std::string getClientInfo();
    Client(std::string Initial_FirstName, std::string Initial_LastName, std::string Initial_PersonalID);
    ~Client();
    std::string getfirstName();
    std::string getlastName();
    std::string getpersonalID();
    void setfirstName(std::string Changed_FirstName);
    void setlastName(std::string Changed_LastName);



};


#endif //CARRENTAL_CLIENT_H
