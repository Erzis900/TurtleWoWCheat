#pragma once

namespace Utils
{
	template<typename T>
	T Read(DWORD address);

	template<typename T>
	void Write(DWORD address, const T& value);

	DWORD ResolveChain(DWORD base, std::vector<DWORD> offsets);
	void Patch(DWORD address, std::vector<BYTE> bytes);
	void NOP(DWORD address, int count);
	bool IsNOP(DWORD address, int count);
}