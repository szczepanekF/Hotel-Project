#include "gMain.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
#include "typedefs.h"
#include "exceptions/ClientError.h"
#include "model/Client.h"

wxBEGIN_EVENT_TABLE(gMain,wxFrame)
    EVT_BUTTON(10001,gMain::OnButtonClicked)

wxEND_EVENT_TABLE()
gMain::gMain() :wxFrame(nullptr,wxID_ANY,"Hotel Reservation App",wxPoint(30,30),wxSize(800,600))
{
    connection = new C_client();


    m_btn1 = new wxButton(this, 10001,"Click Me",wxPoint(10,10),wxSize(150,50));
    m_txt1 = new wxTextCtrl(this, wxID_ANY,"",wxPoint(10,70),wxSize(300,30));
    m_list1 = new wxListBox(this, wxID_ANY,wxPoint(10,110),wxSize(300,300));

//    if(!connection->createConnection()) {
//        errorMessage("NO CONNECTION");
//
//        return;
//    }






}

gMain::~gMain() {
    delete connection;
}

void gMain::errorMessage(std::string message) {
    this->Hide();
    const wxColour* bg= new wxColour(252, 242, 238);
    this->SetBackgroundColour(*bg);
    text = new wxStaticText(this,wxID_ANY,"ERROR\nNO CONNECTION",wxDefaultPosition,wxDefaultSize,wxALIGN_CENTRE_HORIZONTAL);
    boxsizer = new wxBoxSizer(wxVERTICAL);
    boxsizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxFont font (16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
    text->SetFont(font);
    text->SetForegroundColour(*wxRED);
    boxsizer->Add(text,0,wxALIGN_CENTER);
    boxsizer2->Add(boxsizer,1,wxALIGN_CENTER|wxALL,200);
    this->SetSizer(boxsizer2);
}
void gMain::OnButtonClicked(wxCommandEvent &evt) {
    m_list1->AppendString(m_txt1->GetValue());
    m_txt1->Clear();
    delete m_btn1;
    evt.Skip();
}
