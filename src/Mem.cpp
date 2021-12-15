#include "mem.hpp"

uintptr_t FindDynamicAddress(uintptr_t ptr, unsigned offsets[], size_t size)
{
    uintptr_t addr = ptr;

    for (size_t i = 0; i < size; i++)
    {
        addr = *(uintptr_t *)addr;
        addr += offsets[i];

        if (*(int *)addr == 0)
        { 
            return 0;
        }
    }

    return addr;
}

void Patch(char* dst, char* src, size_t size)
{
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, src, size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

bool Detour(void* hookedFunc, void* myFunc, size_t size)
{
    if (size < 5)
    {
        return false;
    }

    DWORD dwProtect;
    VirtualProtect(hookedFunc, size, PAGE_EXECUTE_READWRITE, &dwProtect);

    memset(hookedFunc, 0x90, size); // memset nop
    uintptr_t relative_addr = ((uintptr_t)myFunc - (uintptr_t)hookedFunc) - 5;

    *(unsigned char *)hookedFunc = 0xE9; // replace with jmp
    *(uintptr_t *)((uintptr_t)hookedFunc + 1) = relative_addr;
    VirtualProtect(hookedFunc, size, dwProtect, &dwProtect);

    return true;
}

char* TrampHook(char* src, char* dst, size_t size)
{
    if (size < 5)
    {
        return 0;
    }

    char* gateway = (char *)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(gateway, src, size);

    uintptr_t gateJmpAddress = (uintptr_t)(src - gateway - 5);
    *(gateway + size) = (char)0xE9;
    *(uintptr_t *)(gateway + size + 1) = gateJmpAddress;

    if (Detour(src, dst, size))
    {
        return gateway;
    }
    else
    {
        return NULL;
    }
}

extern "C"
{
int CompareByteArray(PBYTE Data, PBYTE Signature)
{
	for (; *Signature; ++Signature, ++Data)
	{
		if (*Signature == '\x00')
		{
			continue;
		}
		if (*Data != *Signature)
		{
			return false;
		}
	}
	return true;
}

PBYTE FindSignature(PBYTE BaseAddress, DWORD ImageSize, PBYTE Signature)
{
	BYTE First = Signature[0];
	PBYTE Max = BaseAddress + ImageSize - strlen((PCHAR) Signature);

	for (; BaseAddress < Max; ++BaseAddress)
	{
		if (*BaseAddress != First)
		{
			continue;
		}
		if (CompareByteArray(BaseAddress, Signature))
		{
			return BaseAddress;
		}
	}
	return NULL;
}
}
