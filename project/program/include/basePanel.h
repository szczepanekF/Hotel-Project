//
// Created by student on 08.01.2023.
//

#ifndef HOTELPROJECT_BASEPANEL_H
#define HOTELPROJECT_BASEPANEL_H
#include "wx/wx.h"

class cMain;

class basePanel : public wxPanel{
public:
    basePanel(cMain* parent);

    virtual ~basePanel() = 0;
protected:
    cMain* parent;

    wxBoxSizer* verticalSizer = nullptr;
    wxBoxSizer* horizontalSizer= nullptr;

};


#endif //HOTELPROJECT_BASEPANEL_H
