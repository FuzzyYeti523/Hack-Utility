// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

DWORD jumpback;

void __declspec(naked) increase_bullet_when_you_shoot()
{
    __asm
    {
        inc[esi]
        push edi
        mov edi, [esp + 0x14]
        lea esi, [esp + 0x28]
        jmp[jumpback];
    }
}


DWORD WINAPI HackThread(HMODULE hModule)
{

    FILE* f;  
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    uintptr_t BaseModuleAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(L"ac_client.exe"));
    std::cout << "Bullet Ammo Hack" << '\n';
    std::cout<<"Your Base Module address is " << std::hex << "Ox" << BaseModuleAddress << '\n';

    uintptr_t AmmoDecreaseFunction = BaseModuleAddress + 0x637E9;
    jumpback = (DWORD)AmmoDecreaseFunction + 11;
    Hook((void*)AmmoDecreaseFunction, increase_bullet_when_you_shoot, 11);



    


    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            std::cout << "Hacks off " << '\n';
            break;
        }
        



    }








    fclose(f);
   // FreeConsole();
    FreeLibraryAndExitThread(hModule,0);




}





BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(HackThread), hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

