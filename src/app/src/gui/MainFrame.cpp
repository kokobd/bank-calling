#include "MainFrame.h"
#include <wx/menu.h>
#include "DataPanel.h"
#include "ControlPanel.h"
#include <wx/sizer.h>

namespace Zelinf {
namespace BankCalling {
namespace App {

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("银行叫号模拟系统")) {
    createMenus();
    SetBackgroundColour(wxColor("#39393A"));

    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    dataPanel = new DataPanel(this, bank);
    controlPanel = new ControlPanel(this);
    sizer->Add(dataPanel, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));
    sizer->Add(controlPanel, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));
    SetSizer(sizer);

    Center();
}

void MainFrame::createMenus() {
    // create ui
    auto *menuBar = new wxMenuBar;

    auto *fileMenu = new wxMenu;
    wxMenuItem *exit = new wxMenuItem(fileMenu, wxID_ANY, wxT("退出"));
    fileMenu->Append(exit);

    auto *helpMenu = new wxMenu;
    wxMenuItem *help = new wxMenuItem(helpMenu, wxID_ANY, wxT("帮助"));
    wxMenuItem *about = new wxMenuItem(helpMenu, wxID_ANY, wxT("关于"));
    helpMenu->Append(help);
    helpMenu->Append(about);

    menuBar->Append(fileMenu, wxT("文件"));
    menuBar->Append(helpMenu, wxT("帮助"));
    SetMenuBar(menuBar);

    // configure event handlers
    fileMenu->Bind(wxEVT_MENU, [this](wxCommandEvent &evt) -> void {
        Close();
    }, exit->GetId());
}

}
}
}

