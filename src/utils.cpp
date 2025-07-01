#include <pch.h>
#include "utils.h"

namespace Utils
{
	template<typename T>
	T Read(DWORD address)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		T value = *(T*)(address);

		VirtualProtect((LPVOID*)address, sizeof(T), oldProtect, &oldProtect);

		return value;
	}

	template<typename T>
	void Write(DWORD address, const T& value)
	{
		DWORD oldProtect;

		VirtualProtect((LPVOID*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		*(T*)(address) = value;

		VirtualProtect((LPVOID*)address, sizeof(T), oldProtect, &oldProtect);
	}

	DWORD ResolveChain(DWORD base, std::vector<DWORD> offsets)
	{
		for (auto& o : offsets)
		{			
			base = Read<DWORD>(base);
			base += o;
		}

		return base;
	}

	void Patch(DWORD address, std::vector<BYTE> bytes)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((LPVOID*)address, bytes.data(), bytes.size());

		VirtualProtect((LPVOID*)address, bytes.size(), oldProtect, &oldProtect);
	}

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