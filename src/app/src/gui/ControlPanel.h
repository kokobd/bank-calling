#pragma once

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/slider.h>

namespace Zelinf {
namespace BankCalling {
namespace App {

class ControlPanel : public wxPanel {
public:
    explicit ControlPanel(wxWindow *parent);

private:
    wxButton *btnUpdateParams;
    wxTextCtrl *numOfCusMean;
    wxTextCtrl *numOfCusStdDev;
    wxTextCtrl *serTimeMean;
    wxTextCtrl *serTimeStdDev;

    wxSlider *sliderSpeed;
    wxButton *btnStartStop;
    wxButton *btnPauseResume;

    void registerControllers();

    void paintUI();

};

}
}
}
