#include "wx/wx.h"
#include "gMain.h"
#include "typedefs.h"

#ifndef HOTELPROJECT_TEST_H
#define HOTELPROJECT_TEST_H


class cApp : public wxApp{
private:
        gMain* mainFrame = nullptr;
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
