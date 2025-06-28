#include "pch.h"
#include "base.h"
#include <iostream>

DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
	Base::Data::hModule = (HMODULE)lpThreadParameter;
	Base::Init();

	// TODO move this to menu, was just testing, also ugly code
	DWORD oldProtect;
	VirtualProtect((LPVOID)(Base::Addr::base + 0x3C625F), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(uint16_t*)(Base::Addr::base + 0x3C625F) = 0x9090; // Infinite jump

	uint8_t nops[3] = { 0x90, 0x90, 0x90 };
	memcpy((void*)(Base::Addr::base + 0x3C63DA), nops, 3); // No fall damage
	VirtualProtect((LPVOID)(Base::Addr::base + 0x3C625F), 2, oldProtect, &oldProtect);

	return TRUE;
}

DWORD WINAPI ExitThread(LPVOID lpThreadParameter)
{
	if (!Base::Data::Detached)
	{
		Base::Data::Detached = true;
		FreeLibraryAndExitThread(Base::Data::hModule, TRUE);
	}
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if(!Base::Data::Detached)
			CreateThread(nullptr, 0, ExitThread, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}