#include "wx/wx.h"
#include "cMain.h"
#include "typedefs.h"
#include "LoginPanel.h"
#include "RegistrationPanel.h"
#include "socket/C_client.h"


#ifndef HOTELPROJECT_TEST_H
#define HOTELPROJECT_TEST_H


class cApp : public wxApp{
private:
        cMain* m_Frame = nullptr;
        C_client* connection = nullptr;
        ClientRepositoryPtr clients;
        RoomRepositoryPtr rooms;
        ReservationRepositoryPtr currRes;
        ReservationRepositoryPtr archRes;


public:
    cApp();
    ~cApp();

    bool OnInit() override;
};


#endif //HOTELPROJECT_TEST_H
