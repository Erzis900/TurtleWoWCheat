#pragma once

namespace Utils
{
	DWORD ResolveChain(DWORD base, const std::vector<DWORD>& offsets);
	void Patch(DWORD address, const std::vector<DWORD>& bytes);
	void NOP(DWORD address, int count);
	bool IsNOP(DWORD address, int count);
}