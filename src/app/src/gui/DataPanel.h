#pragma once

#include <wx/panel.h>
#include <wx/grid.h>
#include <memory>

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


class DataPanel : public wxPanel {
private:
    std::shared_ptr<Bank> bank;
public:
    using Zelinf::BankCalling::Service::Bank;

    explicit DataPanel(wxWindow *parent, std::shared_ptr<Bank> bank);

private:
    wxGrid *windowInfo;
    wxGrid *queueInfo;

    void initWindowInfo();

    void updateWindowInfo();

    void initQueueInfo();

    void updateQueueInfo();

public:
    /**
     * Update information from the provided std::shared_ptr<Bank>.
     * Bank will be locked while reading information.
     */
    void updateInfos();
};

}
}
}