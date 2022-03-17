#include <iostream>

#include "model/Client.h"

using namespace std;

int main()
{

    Client a("Milosz","Wojtaszczyk","242567");
    Client* b = new Client("Filip","Szczepanek","242544");

    cout<<a.GetClientInfo()<<'\n';
    cout<<b->GetClientInfo()<<'\n';
    a.SetClientFirstName(" ");
    cout<<b->GetClientFirstName()<<'\n';
    cout<<a.GetClientInfo()<<'\n';
    delete b;

    return 0;
}
