#pragma once
#include <cstdint>

namespace Utils
{
	template<typename T>
	T Read(uintptr_t address)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		T value = *(T*)(address);

		VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);

		return value;
	}

	template<typename T>
	void Write(uintptr_t address, const T& value)
	{
		DWORD oldProtect;
		VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

		*(T*)(address) = value;

		VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);
	}

	uintptr_t ResolveChain(uintptr_t base, const std::vector<std::ptrdiff_t>& offsets);
	void Patch(uintptr_t address, const std::vector<BYTE>& bytes);
	void NOP(uintptr_t address, int count);

	template<typename T>
	class Protected
	{
	public:
		constexpr Protected(T* address) : address(address) {}
		Protected(const Protected&) = default;
		Protected& operator=(const Protected&) = default;
		~Protected() = default;

		Protected<T>& operator=(const T& value) {
			Write<T>(reinterpret_cast<uintptr_t>(address), value);
			return *this;
		}
		T operator*() const {
			return Read<T>(reinterpret_cast<uintptr_t>(address));
		}

	private:
		T* const address;
	};
}