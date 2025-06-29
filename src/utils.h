#pragma once

namespace Utils
{
	DWORD resolveChain(DWORD base, std::vector<DWORD> offsets);
	void NOP(DWORD address, int count);
	bool IsNOP(DWORD address, int count);
}