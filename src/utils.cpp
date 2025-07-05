#include <pch.h>
#include "utils.h"
#include <algorithm>

namespace Utils
{
	constexpr DWORD nopCode = 0x90;

	DWORD ResolveChain(DWORD base, const std::vector<int>& offsets)
	{
		for (auto& o : offsets)
		{
			base = Read<DWORD>(base);
			base += o;
		}

		return base;
	}

	void Patch(DWORD address, const std::vector<BYTE>& bytes)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((LPVOID)address, bytes.data(), bytes.size());

		VirtualProtect((LPVOID)address, bytes.size(), oldProtect, &oldProtect);
	}

	void NOP(DWORD address, int count)
	{
		Patch(address, std::vector<BYTE>(count, nopCode));
	}

	bool IsNOP(DWORD address, int count)
	{
		for (int i = 0; i < count; i++)
		{
			if (Read<BYTE>(address + i) != nopCode)
				return false;
		}

		return true;
	}
}