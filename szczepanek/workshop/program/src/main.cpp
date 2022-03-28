#include <iostream>

#include "model/Client.h"

using namespace std;

int main()
{

    Client a("Milosz","Wojtaszczyk","242567");
    Client* b = new Client("Filip","Szczepanek","242544");

    cout<<a.getClientInfo()<<'\n';
    cout<<b->getClientInfo()<<'\n';
    a.setfirstName(" ");
    cout<<b->getfirstName()<<'\n';
    cout<<a.getClientInfo()<<'\n';
    delete b;

    return 0;
}
