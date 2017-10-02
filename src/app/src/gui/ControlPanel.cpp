#include "ControlPanel.h"
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/toplevel.h>
#include <wx/valtext.h>

namespace Zelinf {
namespace BankCalling {
namespace App {

ControlPanel::ControlPanel(wxWindow *parent, BankRunner &bankRunner)
        : wxPanel(parent), bankRunner(bankRunner) {
    paintUI();
    registerControllers();
}

void ControlPanel::paintUI() {
    auto *numberOfCustomersBox = new wxStaticBox(this, wxID_ANY, wxT("顾客数量"));
    {
        auto *mean = new wxStaticText(numberOfCustomersBox, wxID_ANY, wxT("mean"));
        auto *stddev = new wxStaticText(numberOfCustomersBox, wxID_ANY, wxT("stddev"));
        numOfCusMean = new wxTextCtrl(numberOfCustomersBox, wxID_ANY, wxT("0"));
        numOfCusStdDev = new wxTextCtrl(numberOfCustomersBox, wxID_ANY, wxT("1"));

        auto *sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(mean, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_TOP));
        sizer->Add(numOfCusMean, wxSizerFlags().Border(wxRIGHT, 5));
        sizer->Add(stddev, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_TOP));
        sizer->Add(numOfCusStdDev, wxSizerFlags().Border(wxRIGHT, 5));
        numberOfCustomersBox->SetSizer(sizer);
    }

    auto *expectedServiceTimeBox = new wxStaticBox(this, wxID_ANY, wxT("需要的服务时间"));
    {
        auto *mean = new wxStaticText(expectedServiceTimeBox, wxID_ANY, wxT("mean"));
        auto *stddev = new wxStaticText(expectedServiceTimeBox, wxID_ANY, wxT("stddev"));
        serTimeMean = new wxTextCtrl(expectedServiceTimeBox, wxID_ANY, wxT("0"));
        serTimeStdDev = new wxTextCtrl(expectedServiceTimeBox, wxID_ANY, wxT("1"));

        auto *sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(mean, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_TOP));
        sizer->Add(serTimeMean, wxSizerFlags().Border(wxRIGHT, 5));
        sizer->Add(stddev, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_TOP));
        sizer->Add(serTimeStdDev, wxSizerFlags().Border(wxRIGHT, 5));
        expectedServiceTimeBox->SetSizer(sizer);
    }
    btnUpdateParams = new wxButton(this, wxID_ANY, wxT("应用参数"));

    auto *controls = new wxPanel(this);
    {
        auto *speedText = new wxStaticText(controls, wxID_ANY, wxT("运行速度"));
        sliderSpeed = new wxSlider(controls, wxID_ANY, 50, 0, 100);
        btnStartStop = new wxButton(controls, wxID_ANY, wxT("开始"));
        btnPauseResume = new wxButton(controls, wxID_ANY, wxT("暂停"));
        auto *sizer = new wxGridBagSizer(5, 5);
        sizer->Add(speedText, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALIGN_CENTER);
        sizer->Add(sliderSpeed, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND);
        sizer->Add(btnStartStop, wxGBPosition(2, 0));
        sizer->Add(btnPauseResume, wxGBPosition(2, 1));
        controls->SetSizer(sizer);
    }

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(numberOfCustomersBox, wxSizerFlags().Expand().Proportion(1));
    sizer->Add(expectedServiceTimeBox, wxSizerFlags().Expand().Proportion(1));
    sizer->Add(btnUpdateParams, wxSizerFlags().Align(wxALIGN_TOP | wxALIGN_CENTER));
    sizer->Add(controls, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxTOP, 17));
    SetSizer(sizer);
}


void ControlPanel::registerControllers() {
    btnUpdateParams->Bind(wxEVT_BUTTON, [](wxCommandEvent &event) {
        std::cout << "Update params" << std::endl;
    }, btnUpdateParams->GetId());
}

}
}
}
