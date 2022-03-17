#include <iostream>
#include "math_helpers.h"
#include "model/Client.h"

using namespace std;

int main()
{

    Client c1("Milosz","Wojtaszczyk","242567");
    Client* c2 = new Client("Filip","Szczepanek","242544");

    cout<<c1.GetClientInfo()<<'\n';
    cout<<c2->GetClientInfo()<<'\n';
    c1.SetClientFirstName(" ");
    cout<<c1.GetClientFirstName()<<'\n';
    cout<<c1.GetClientInfo()<<'\n';
    delete c2;

    return 0;
}
