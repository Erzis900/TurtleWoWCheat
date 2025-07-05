#include <pch.h>
#include <base.h>
#include <vector>
#include "utils.h"

//Data
HMODULE           Base::Data::hModule    = (HMODULE)NULL;
void*             Base::Data::pDeviceTable[D3DDEV9_LEN];
LPDIRECT3DDEVICE9 Base::Data::pDxDevice9 = (LPDIRECT3DDEVICE9)NULL;
HWND              Base::Data::hWindow    = (HWND)NULL;
mem::voidptr_t    Base::Data::pEndScene  = (mem::voidptr_t)NULL;
EndScene_t        Base::Data::oEndScene  = (EndScene_t)NULL;
WndProc_t         Base::Data::oWndProc   = (WndProc_t)NULL;
#if defined(MEM_86)
mem::size_t       Base::Data::szEndScene = 7;
#elif defined(MEM_64)
mem::size_t       Base::Data::szEndScene = 15;
#endif
UINT              Base::Data::WmKeys[0xFF];
bool              Base::Data::Detached   = false;
bool              Base::Data::ToDetach   = false;
bool              Base::Data::ShowMenu   = true;
bool              Base::Data::InitImGui  = false;

namespace Base
{
	namespace Addr
	{
		DWORD base = (DWORD)GetModuleHandle(nullptr);
		DWORD infiniteJump = base + Offset::infiniteJump;
		DWORD noFallDamage = base + Offset::noFallDamage;
		DWORD airSwim = base + Offset::airSwim;
		DWORD superFly = base + Offset::superFly;
		char* version = (char*)0x00837C04;
	}

	namespace Offset
	{
		int player = 0x000AE4EC;
		int infiniteJump = 0x3C625F;
		int noFallDamage = 0x3C63DA;
		int airSwim = 0x3C620D;
		int superFly = 0x2341BC;
	}

	namespace Default
	{
		float fallingSpeed = 64.f;
		float walkingSpeed = 7.f;
		float wallClimb = 0.64f;
	}

	//Functions

	bool Init()
	{
		Hooks::Init();

		FILE* fp;
		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w", stdout);
		return true;
	}

	bool Shutdown()
	{
		Hooks::Shutdown();
		return true;
	}

	bool Detach()
	{
		Base::Shutdown();
		CreateThread(nullptr, 0, ExitThread, Data::hModule, 0, nullptr);
		return true;
	}
}