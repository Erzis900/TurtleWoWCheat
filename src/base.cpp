#include <pch.h>
#include <base.h>
#include <vector>
#include <spdlog/spdlog.h>
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
	//Functions
	bool Init()
	{
		Hooks::Init();
		FILE* fp;
		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w", stdout);
		spdlog::info("Cheat initialized!");
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

namespace Addr
{
	uintptr_t player = 0x4AE4EC;
	uintptr_t infiniteJump = 0x7C625F;
	uintptr_t noFallDamage = 0x7C63DA;
	uintptr_t airSwim = 0x7C620D;
	uintptr_t superFly = 0x6341BC;
	uintptr_t unlockZoom = 0x511459;
	uintptr_t antiRoot = 0x6163DB;
	uintptr_t version = 0x00837C04;
}

namespace Ptr
{
	extern uintptr_t* entityManager = (uintptr_t*)0x00B41414;
}

namespace Default
{
	float fallingSpeed = 64.f;
	float walkingSpeed = 7.f;
	float wallClimb = 0.64f;
	float jumpGravity = -7.955547333f;
}