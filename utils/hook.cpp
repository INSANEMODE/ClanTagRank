
//#include "../pch.h"
#include <windows.h>
#include <vector>
#include <cassert>
#include <mutex>


namespace utils::hook
{
	void* allocate_stub_memory(size_t size)
	{
		return VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}
}
