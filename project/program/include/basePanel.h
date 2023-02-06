//
// Created by student on 08.01.2023.
//

#ifndef HOTELPROJECT_BASEPANEL_H
#define HOTELPROJECT_BASEPANEL_H
#include "wx/wx.h"

class gMain;

class basePanel : public wxPanel{
public:
    basePanel(gMain* parent);

    virtual ~basePanel() = 0;
protected:
    gMain* parent;

    wxBoxSizer* verticalSizer = nullptr;
    wxBoxSizer* horizontalSizer= nullptr;

};


#endif //HOTELPROJECT_BASEPANEL_H
