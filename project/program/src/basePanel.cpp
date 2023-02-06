//
// Created by student on 08.01.2023.
//

#include "basePanel.h"
#include "gMain.h"

basePanel::basePanel(gMain *parent) : parent(parent),wxPanel(parent) {
    this->SetBackgroundColour(wxColour(222,244,222));
    verticalSizer = new wxBoxSizer(wxVERTICAL);
    horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
}

basePanel::~basePanel(){};
