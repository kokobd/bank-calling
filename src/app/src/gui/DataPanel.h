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

class BankRunner;

class DataPanel : public wxPanel {
private:
    BankRunner &bankRunner;
public:

    explicit DataPanel(wxWindow *parent, BankRunner &bankRunner);

private:
    wxGrid *windowInfo;
    wxGrid *queueInfo;

    void initWindowInfo();

    void updateWindowInfo();

    void initQueueInfo();

    void updateQueueInfo();

    void onUpdateInfo(wxCommandEvent &);

public:
    /**
     * Update information from the provided std::shared_ptr<Bank>.
     * Bank will be locked while reading information.
     */
    void updateInfo();
};

}
}
}