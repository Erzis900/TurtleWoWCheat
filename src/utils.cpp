#include <pch.h>
#include "utils.h"
#include <algorithm>

namespace Utils
{
	constexpr DWORD nopCode = 0x90;

	DWORD ResolveChain(DWORD base, const std::vector<DWORD>& offsets)
	{
		for (auto& o : offsets)
		{
			base = *(DWORD*)base;
			base += o;
		}

		return base;
	}

	void Patch(DWORD address, const std::vector<DWORD>& bytes)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((LPVOID*)address, bytes.data(), bytes.size());

		VirtualProtect((LPVOID*)address, bytes.size(), oldProtect, &oldProtect);
	}

	void NOP(DWORD address, int count)
	{
		Patch(address, std::vector<DWORD>(count, nopCode));
	}

	bool IsNOP(DWORD address, int count)
	{
		const BYTE* begin = reinterpret_cast<BYTE*>(address);
		const BYTE* end = reinterpret_cast<BYTE*>(address) + count;
		return std::all_of(begin, end, [](BYTE byte) { return byte == nopCode; });
	}
}