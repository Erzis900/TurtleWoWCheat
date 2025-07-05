#pragma once

namespace Utils
{
	template<typename T>
	T Read(DWORD address)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		T value = *(T*)(address);

		VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);

		return value;
	}

	template<typename T>
	void Write(DWORD address, const T& value)
	{
		DWORD oldProtect;

		VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		*(T*)(address) = value;

		VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);
	}

	// DWORD ResolveChain(DWORD base, std::vector<DWORD> offsets);
	// void Patch(DWORD address, std::vector<DWORD> bytes);
	DWORD ResolveChain(DWORD base, const std::vector<DWORD>& offsets);
	void Patch(DWORD address, const std::vector<BYTE>& bytes);
	void NOP(DWORD address, int count);
	bool IsNOP(DWORD address, int count);

	template<typename T>
	class Protected
	{
	public:
		constexpr Protected(T* address) : address(address) {}
		Protected(const Protected&) = default;
		Protected& operator=(const Protected&) = default;
		~Protected() = default;

		Protected<T>& operator=(const T& value) {
			Write<T>(reinterpret_cast<DWORD>(address), value);
			return *this;
		}
		T operator*() const {
			return Read<T>(reinterpret_cast<DWORD>(address));
		}
	private:
		const T* address;
	};
}