//Author : FuzzyYeti757
//Date   : 2026-02-24 
//Description : Review how external hackwork

#include"FindProcessID.h" //All process has it's own unique process id and we need this for gamehacking
#include"GetBaseModuleAddress.h"
#include<iostream>
#include"mem.h"




int main(int argc, char**argv)
{
	DWORD ProcessID = FindProcessID(L"ac_client.exe");
	std::cout << "Process ID is " << ProcessID << '\n';
	bool brecoil = false;
	if (ProcessID == 0)
	{
		std::cout << "Can't find your process id " << '\n';
		
	}

	else
	{
		uintptr_t BaseModuleAdress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");

		std::cout << "Your Base Module Address is " << std::hex << BaseModuleAdress << '\n';

		uintptr_t PlayerLocalEntity = BaseModuleAdress + 0x10F4F4;

		std::cout << "Your Player Local Entity is  " << std::hex << PlayerLocalEntity << '\n';

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessID);


		uintptr_t RecoilFunctionStart = BaseModuleAdress + 0x62020;
		uintptr_t RecoilFunctionCaller = BaseModuleAdress + 0x63786;



		DWORD dwexit = 0;
		while (GetExitCodeProcess(hProcess,&dwexit) && dwexit==STILL_ACTIVE )
		{
			if (GetAsyncKeyState(VK_NUMPAD7)&1)
			{
				brecoil = !brecoil;
				if (brecoil == true)
				{
					std::cout << "Recoil hacks on " << '\n';
					mem::NopEX((BYTE*)RecoilFunctionCaller,10,hProcess);
				}
				if (brecoil == false)
				{
					std::cout << "Recoil hack off " << '\n';
					mem::PatchEX((BYTE*)RecoilFunctionCaller,(BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, hProcess);

				}
				
				
			}


		}
			
	}


	return 0;


}