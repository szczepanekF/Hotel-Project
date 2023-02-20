//
// Created by student on 20.02.2023.
//

#ifndef HOTELPROJECT_BASELOGGEDPANEL_H
#define HOTELPROJECT_BASELOGGEDPANEL_H

#include "basePanel.h"

class cMain;
class baseLoggedPanel: public basePanel {
public:
    baseLoggedPanel(cMain *parent);
    virtual ~baseLoggedPanel();

    void RefreshAfterLogging();
protected:
    wxStaticText* fname;
    wxStaticText* lname;
    wxStaticText* balance;
    wxBoxSizer* balanceInfoSizer;


};


#endif //HOTELPROJECT_BASELOGGEDPANEL_H
