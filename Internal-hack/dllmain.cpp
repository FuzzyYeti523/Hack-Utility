// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include<Windows.h>




DWORD WINAPI HackThread(HMODULE hmodule)
{

    //Create console 
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Recoil DLL Injected" << '\n';



    uintptr_t moduleBase = reinterpret_cast<uintptr_t> (GetModuleHandle(L"ac_client.exe"));

    uintptr_t RecoilFunctionCaller = moduleBase + 0x63786;

    uintptr_t AmmoDecreaseFunction = moduleBase + 0x637E9;

    uintptr_t ChangeFunction   = moduleBase + 0x2CA5E;

    bool breocil = false;
    bool bInfinity = false;


    

    while (true)
    {

        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD7) & 1)
        {
            breocil = !breocil;

            if (breocil)
            {
                std::cout << "Recoil Hack on " << '\n';
                mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
            }

            else
            {
                std::cout << "Recoil Hack off " << '\n';
                mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
            }
        }

        



        



    }
    mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
  
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hmodule, 0);

  

}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        /*CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));*/
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

