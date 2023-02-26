//
// Created by student on 20.02.2023.
//

#ifndef HOTELPROJECT_BASELOGGEDPANEL_H
#define HOTELPROJECT_BASELOGGEDPANEL_H

#include "basePanel.h"

class cMain;
class baseLoggedPanel: public basePanel {
protected:
    wxStaticText* fname;
    wxStaticText* cType;
    wxStaticText* balance;

    wxBoxSizer* balanceInfoSizer;
public:
    baseLoggedPanel(cMain *parent);
    virtual ~baseLoggedPanel() = default;

    void SetOnLogging();
    void RefreshBalance();



};


#endif //HOTELPROJECT_BASELOGGEDPANEL_H
