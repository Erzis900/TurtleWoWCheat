#include <pch.h>
#include <base.h>
#include <vector>

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

DWORD resolveChain(DWORD base, std::vector<DWORD> offsets)
{
	for (auto& o : offsets)
	{
		base = *(DWORD*)base;
		base += o;
	}

	return base;
}

namespace Base::Addr
{
	DWORD base = (DWORD)GetModuleHandle(nullptr);
	DWORD player = resolveChain(Base::Addr::base + Base::Offset::player, { 0x5C, 0x9A8 });
	float* wallClimb = (float*)0x0080DFFC;
	char* version = (char*)0x00837C04;
}

namespace Base::Offset
{
	DWORD player = 0x000AE4EC;
}

namespace Base::Default
{
	// TODO pretty useless, we should read those from memory on init
	float fallingSpeed = 64.f;
	float walkingSpeed = 7.f;
	float wallClimb = 0.64;
}

namespace Base::Menu
{
	bool isFallingSpeed = false;
	bool isWalkingSpeed = false;
	bool isWallClimb = false;
}

//Functions

bool Base::Init()
{
	Hooks::Init();

	FILE* fp;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);

	return true;
}

bool Base::Shutdown()
{
	Hooks::Shutdown();
	return true;
}

bool Base::Detach()
{
	Base::Shutdown();
	CreateThread(nullptr, 0, ExitThread, Data::hModule, 0, nullptr);
	return true;
}