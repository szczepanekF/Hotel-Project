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



    //wxGridSizer* grid = new wxGridSizer(nFieldWidth,nFieldHeight,wxALIGN_CENTER_HORIZONTAL,wxALIGN_CENTER_VERTICAL);
    /*
    for(int x= 0;x<nFieldWidth;x++)
    {
        for(int y=0;y<nFieldHeight;y++)
        {
            btn[y*nFieldWidth+x] = new wxButton(this,1000+(y*nFieldWidth+x));
            grid->Add(btn[y*nFieldWidth+x],1,wxEXPAND | wxALL);
        }
    }
    this->SetSizer(grid);
    grid-Layout();
    */


    connection = new c_client();
    if(!connection->createConnection()) {
        text = new wxStaticText(this,wxID_ANY,"NO CONNECTION",wxPoint(0,0),wxSize(200,200),wxALIGN_CENTER_VERTICAL);

        return;
    }


    ClientRepositoryPtr repo = std::make_shared<ClientRepository>();
    ClientManager manager(repo);
    manager.readClientsFromDB(connection);


    m_btn1 = new wxButton(this, 10001,"Click Me",wxPoint(10,10),wxSize(150,50));
    m_txt1 = new wxTextCtrl(this, wxID_ANY,"",wxPoint(10,70),wxSize(300,30));
    m_list1 = new wxListBox(this, wxID_ANY,wxPoint(10,110),wxSize(300,300));



}

gMain::~gMain() {
    delete connection;
}

void gMain::OnButtonClicked(wxCommandEvent &evt) {
    m_list1->AppendString(m_txt1->GetValue());
    m_txt1->Clear();
    delete m_btn1;
    evt.Skip();
}
