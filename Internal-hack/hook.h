#pragma once
#include"pch.h"

inline bool Hook(void*target,void*function,int len)
{
	// in x86 asembly near jump is 5 byte
	if (len < 5)
	{
		return false;
	}

	DWORD current_protect;
	VirtualProtect(target,len,PAGE_EXECUTE_READWRITE,&current_protect); //have to get access perrsion for read/write

	std::memset(target, 0x90, len); //

	DWORD RelativeOffset = (DWORD)function - (DWORD)target - 5;

	*((BYTE*)target) = 0xE9;  // in x86 environment x86 is near jmp 
    
	*((DWORD*)(((DWORD)RelativeOffset + 1))) = RelativeOffset;


	VirtualProtect(target, len, current_protect, &current_protect);
	return true;

}