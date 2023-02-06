#include "wx/wx.h"
#include "socket/C_client.h"
#ifndef HOTELPROJECT_GMAIN_H
#define HOTELPROJECT_GMAIN_H
#include "managers/ClientManager.h"
#include "managers/RoomManager.h"
#include "managers/ReservationManager.h"
#include "typedefs.h"

class LoginPanel;
class gMain : public wxFrame{
public:
    gMain(C_client* conn,ClientManagerPtr CM,RoomManagerPtr RoomM,ReservationManagerPtr ResM);
    virtual ~gMain();
private:
    LoginPanel* loginP = nullptr;
    wxPanel* registerP = nullptr;
    wxPanel* middleP = nullptr;
    wxPanel* reservationP = nullptr;
    wxPanel* roomsP = nullptr;
    wxPanel* settingsP = nullptr;
    wxBoxSizer* boxsizer2 = nullptr;

    ClientManagerPtr CM;
    RoomManagerPtr RoomM;
    ReservationManagerPtr ResM;
    C_client* connection;
public:
    ClientManagerPtr getCm() const;
    RoomManagerPtr getRoomM() const;
    ReservationManagerPtr getResM() const;
    C_client *getConnection() const;

    //void errorMessage(std::string message);
    void changePanels(unsigned int panelnr);


};


#endif //HOTELPROJECT_GMAIN_H
