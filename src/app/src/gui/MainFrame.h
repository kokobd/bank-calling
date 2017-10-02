#pragma once

#include <wx/frame.h>
#include <memory>
#include "../BankRunner.h"

namespace Zelinf {
namespace BankCalling {
namespace Service {

class Bank;

}
}
}

namespace Zelinf {
namespace BankCalling {
namespace App {

class DataPanel;

class ControlPanel;

class MainFrame : public wxFrame {
private:
    DataPanel *dataPanel;
    ControlPanel *controlPanel;
public:
    MainFrame();

private:
    void createMenus();

    std::shared_ptr<Zelinf::BankCalling::Service::Bank> bank;

    BankRunner bankRunner;
};

}
}
}
