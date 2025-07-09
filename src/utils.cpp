#include <pch.h>
#include "utils.h"
#include <algorithm>

namespace Utils
{
	constexpr BYTE nopCode = 0x90;

	uintptr_t ResolveChain(uintptr_t base, const std::vector<std::ptrdiff_t>& offsets)
	{
		for (auto& o : offsets)
		{
			base = Read<uintptr_t>(base);
			base += o;
		}

		return base;
	}

	void Patch(uintptr_t address, const std::vector<BYTE>& bytes)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((LPVOID)address, bytes.data(), bytes.size());

		VirtualProtect((LPVOID)address, bytes.size(), oldProtect, &oldProtect);
	}

	void NOP(uintptr_t address, int count)
	{
		Patch(address, std::vector<BYTE>(count, nopCode));
	}

	float Distance(const Vec3& a, const Vec3& b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		float dz = a.z - b.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}
}