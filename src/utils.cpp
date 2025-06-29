#include <pch.h>
#include "utils.h"

namespace Utils
{
	DWORD resolveChain(DWORD base, std::vector<DWORD> offsets)
	{
		for (auto& o : offsets)
		{
			base = *(DWORD*)base;
			base += o;
		}

		return base;
	}

	// TODO write a restore function that restores the original bytes
	void NOP(DWORD address, int count)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID*)address, count, PAGE_EXECUTE_READWRITE, &oldProtect);
		
		memset((LPVOID*)address, 0x90, count);

		VirtualProtect((LPVOID*)address, count, oldProtect, &oldProtect);
	}

	bool IsNOP(DWORD address, int count)
	{
		for (int i = 0; i < count; i++)
		{
			if (*(BYTE*)(address + i) != 0x90)
				return false;
		}

		return true;
	}
}