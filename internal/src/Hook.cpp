#include "Hook.h"

bool Hook(void *toHook, void *ourFunct, int len)
{
    if (len < 5)
    {
        return false;
    }

    DWORD oldProtect;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(toHook, 0x90, len);
    DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;


    // our function = ToHook+5+relativeAddress
    // relativeAddress = our function - ToHook - 5
    *(BYTE *)toHook = 0xE9; //jmp opcode
    *(DWORD *)((DWORD)toHook + 1) = relativeAddress;
    VirtualProtect(toHook, len, oldProtect, &oldProtect);
    return true;
}