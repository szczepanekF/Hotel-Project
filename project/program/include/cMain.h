#include "wx/wx.h"
#include "socket/C_client.h"
#ifndef HOTELPROJECT_GMAIN_H
#define HOTELPROJECT_GMAIN_H
#include "managers/ClientManager.h"
#include "managers/RoomManager.h"
#include "managers/ReservationManager.h"
#include "typedefs.h"

class baseLoggedPanel;
class SettingsPanel;
class LoginPanel;
class RegistrationPanel;

class cMain : public wxFrame{
private:
    LoginPanel* loginP = nullptr;
    RegistrationPanel* registerP = nullptr;

    baseLoggedPanel* middleP = nullptr;

    baseLoggedPanel* reservationP = nullptr;
    baseLoggedPanel* roomsP = nullptr;
    SettingsPanel* settingsP = nullptr;
    wxBoxSizer* boxsizer = nullptr;

    ClientManagerPtr CM;
    RoomManagerPtr RoomM;
    ReservationManagerPtr ResM;
    C_client* connection;


public:
    cMain(C_client* conn, ClientManagerPtr& CM, RoomManagerPtr& RoomM, ReservationManagerPtr& ResM);
    virtual ~cMain();


    ClientManagerPtr getCm() const;
    RoomManagerPtr getRoomM() const;
    ReservationManagerPtr getResM() const;
    C_client *getConnection() const;
    void RefreshAllPanelsAfterLogging();
    void RefreshAllPanelsBalance();
    void changePanels(unsigned int panelnr);



};


#endif //HOTELPROJECT_GMAIN_H
