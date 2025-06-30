#pragma once

namespace Utils
{
	DWORD ResolveChain(DWORD base, std::vector<DWORD> offsets);
	void Patch(DWORD address, std::vector<BYTE> bytes);
	void NOP(DWORD address, int count);
	bool IsNOP(DWORD address, int count);
}