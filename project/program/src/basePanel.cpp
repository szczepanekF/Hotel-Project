//
// Created by student on 08.01.2023.
//

#include "basePanel.h"
#include "cMain.h"

basePanel::basePanel(cMain *parent) : parent(parent), wxPanel(parent) {
    this->SetBackgroundColour(wxColour(237,237,233));

    verticalSizer = new wxBoxSizer(wxVERTICAL);
    horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
}

