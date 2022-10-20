//
// Created by student on 06.09.2022.
//
#include "wx/wx.h"
#include "gMain.h"
#ifndef HOTELPROJECT_TEST_H
#define HOTELPROJECT_TEST_H


class cApp : public wxApp{
public:
    cApp();
    ~cApp();

    bool OnInit() override;
private:
    gMain* m_frame1 = nullptr;
};


#endif //HOTELPROJECT_TEST_H
