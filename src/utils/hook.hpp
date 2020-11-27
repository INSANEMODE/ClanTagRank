// Copyright 2020 xensik. All Rights Reserved.

#pragma once

namespace utils::hook
{
	void* allocate_stub_memory(size_t size);

	template<typename ValueType, typename AddressType>
	inline ValueType get(AddressType address)
	{
		return *static_cast<ValueType*>(address);
	}

	template<typename ValueType, typename AddressType>
	inline void set(AddressType address, ValueType value)
	{
		std::memcpy((void*)address, &value, sizeof(value));
	}

	template<typename ValueType, typename AddressType>
	inline void set(AddressType address, const ValueType* data, size_t length)
	{
		std::memcpy((void*)address, data, sizeof(ValueType) * length);
	}

	template<typename AddressType>
	inline void nop(AddressType address, size_t length)
	{
		std::memset((void*)address, 0x90, length);
	}

	template<typename FuncType, typename AddressType>
	inline void jump(AddressType address, FuncType func)
	{
		set<uint8_t>(address, 0xE9);
		set<uintptr_t>((uintptr_t)address + 1, (uintptr_t)func - (uintptr_t)address - 5);
	}

	template<typename FuncType, typename AddressType>
	inline void call(AddressType address, FuncType func)
	{
		set<uint8_t>(address, 0xE8);
		set<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)address - 5);
	}

	template<typename FuncType, typename AddressType>
	FuncType detour(AddressType target, FuncType hook, const int len)
	{
		uintptr_t tampoline = (uintptr_t)allocate_stub_memory(len + 5);

		std::memcpy((void*)tampoline, (void*)target, len);

		set<uint8_t>(tampoline + len, 0xE9);
		set<int>((uintptr_t)tampoline + len + 1, (intptr_t)target - (intptr_t)tampoline - 5);

		set<uint8_t>(target, 0xE9);
		set<int>((uintptr_t)target + 1, (intptr_t)hook - (intptr_t)target - 5);

		int pos = len - 5;
		if (pos > 0) nop((uintptr_t)target + 5, pos);

		return reinterpret_cast<FuncType>(tampoline);
	}

namespace vp
{
	template<typename ValueType, typename AddressType>
	inline void set(AddressType address, ValueType value)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename ValueType, typename AddressType>
	inline void set(AddressType address, const ValueType* data, size_t length)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(ValueType) * length, PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memcpy((void*)address, data, sizeof(ValueType) * length);

		VirtualProtect((void*)address, sizeof(ValueType) * length, oldProtect, &oldProtect);
	}

	template<typename AddressType>
	inline void nop(AddressType address, size_t length)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memset((void*)address, 0x90, length);

		VirtualProtect((void*)address, length, oldProtect, &oldProtect);
	}

	template<typename FuncType, typename AddressType>
	inline void jump(AddressType address, FuncType func)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		hook::set<uint8_t>(address, 0xE9);
		hook::set<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)address - 5);

		VirtualProtect((void*)address, 5, oldProtect, &oldProtect);
	}

	template<typename FuncType, typename AddressType>
	inline void call(AddressType address, FuncType func)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		hook::set<uint8_t>(address, 0xE8);
		hook::set<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)address - 5);

		VirtualProtect((void*)address, 5, oldProtect, &oldProtect);
	}

	template<typename FuncType, typename AddressType>
	FuncType detour(AddressType target, FuncType hook, const int len)
	{
		uintptr_t tampoline = (uintptr_t)allocate_stub_memory(len + 5);

		std::memcpy((void*)tampoline, (void*)target, len);

		hook::set<uint8_t>(tampoline + len, 0xE9);
		hook::set<int>((uintptr_t)tampoline + len + 1, (intptr_t)target - (intptr_t)tampoline - 5);

		DWORD oldProtect;
		VirtualProtect((void*)target, len, PAGE_EXECUTE_READWRITE, &oldProtect);

		hook::set<uint8_t>(target, 0xE9);
		hook::set<int>((uintptr_t)target + 1, (intptr_t)hook - (intptr_t)target - 5);

		int pos = len - 5;
		if (pos > 0) hook::nop((uintptr_t)target + 5, pos);

		VirtualProtect((void*)target, len, oldProtect, &oldProtect);

		return reinterpret_cast<FuncType>(tampoline);
	}
}

}
