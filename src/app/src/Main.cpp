#include "Main.h"
#include "gui/MainFrame.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"

IMPLEMENT_APP(Zelinf::BankCalling::App::BankCallingApp);
#pragma clang diagnostic pop

namespace Zelinf {
namespace BankCalling {
namespace App {

bool BankCallingApp::OnInit() {
    auto *frame = new MainFrame();
    frame->Show(true);

    return true;
}

}
}
}
