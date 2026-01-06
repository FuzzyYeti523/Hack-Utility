#include"GetBaseModuleAddress.h"
#include"FindDMAAddy.h"
#include"FindProcessID.h"
#include<iostream>
int main()
{
	std::cout << " Assult Cube Internal Hack !! " << '\n';
	DWORD ProcessID = FindProcessID(L"ac_client.exe");
	uintptr_t BaseModuleAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

	std::cout << "Process ID : " << ProcessID << '\n';
	std::cout << "Base Module Address " << std::hex << BaseModuleAddress << '\n';

	uintptr_t PlayerEntityAddress = BaseModuleAddress + 0x10F4F4;

	std::cout << "Player Entity Address " << PlayerEntityAddress << '\n';

	HANDLE Current_Handle=OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);

	uintptr_t current_health_ptr = FindDMAAddy(Current_Handle, PlayerEntityAddress, { 0xF8 });

	int current_health = 0;
	ReadProcessMemory(Current_Handle, (BYTE*)current_health_ptr, &current_health, sizeof(current_health), NULL);

	std::cout << std::dec <<"Player Current Health : "<<current_health << '\n';

	int target_health = 6974;
	WriteProcessMemory(Current_Handle, (BYTE*)current_health_ptr, &target_health, sizeof(target_health), NULL);

	std::cout << std::dec << "You overwright your health good job your cheat works well " << '\n';
	ReadProcessMemory(Current_Handle, (BYTE*)current_health_ptr, &current_health, sizeof(current_health), NULL);

	std::cout << std::dec << "Player Current Health : " << current_health << '\n';

	


	
	
}

