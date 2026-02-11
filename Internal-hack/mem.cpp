#include "mem.h"
#include "pch.h"
void mem::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	std::memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);

}

void mem::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	std::memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t mem::FindDMAAddY(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t Base = ptr;
	for (size_t i = 0; i < offsets.size(); i++)
	{
		Base = *(reinterpret_cast<uintptr_t*>(Base));
		Base += offsets[i];
	}
	return Base;
}
