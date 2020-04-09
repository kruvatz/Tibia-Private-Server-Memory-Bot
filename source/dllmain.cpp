// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Character.h"


typedef void(__stdcall* _login1)();




DWORD WINAPI HackThread(HMODULE hModule)
{


	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);


	Character chr = Character(moduleBase);

	_login1 lgn1 = (_login1)(moduleBase + 0xE0340);

	bool att_flag = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_END) & 1)
		{

			chr.~Character();
			break;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1) {


			chr.look_coord(0x8D, 0x12C, 5);



		}


		if (GetAsyncKeyState(VK_F1) & 1)
		{

		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			att_flag = !att_flag;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			chr.debug_print_creatures();
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			chr.debug_print_map();
		}
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			chr.use_hp_pot();
		}


		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			chr.use_mp_pot();
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1)
		{
			chr.open_backpack();
		}

		if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		{
			chr.sell_item(0x10, 0x11D);

		}


		if (GetAsyncKeyState(VK_NUMPAD9) & 1)
		{
			chr.use_consumable_by_id(0xE04);
		}

		if (att_flag) {
			if ((float)chr.get_cHP() / (float)chr.get_mHP() < 0.5) chr.use_consumable_by_id(0xE04);
			if ((float)chr.get_cMP() / (float)chr.get_mMP() < 0.5) chr.use_consumable_by_id(0xE04);

			chr.Attack(chr.get_closest_Mob_ID());
			Sleep(250);
		}

		Sleep(5);
		
	}
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}





BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}