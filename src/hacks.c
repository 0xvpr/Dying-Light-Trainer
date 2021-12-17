#include "offsets.h"
#include "entity.h"
#include "hacks.h"
#include "mem.h"

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <psapi.h>

extern uintptr_t module_base_addr;

bool bGodmode = false;
bool bOneShot = false;
bool bStamina = false;

void hacks_ToggleGodmode(bool bEnabled)
{
    HANDLE      client;
    MODULEINFO  modInfo;
    uintptr_t   godmode_addr;

    unsigned char original[8] = {
        0xF3, 0x0F, 0x11, 0x83, 0x64, 0x09, 0x00, 0x00  // movss [rbx+00000964],xmm0
    };

    unsigned char patch[8] = {
        0xEB, 0x06,  // jmp     $+0x06
        0x90,        // nop
        0x90,        // nop
        0x90,        // nop
        0x90,        // nop
        0x90,        // nop
        0x90         // nop
    };

    client = GetModuleHandleA("gamedll_x64_rwdi.dll");
    GetModuleInformation( GetCurrentProcess(),
                          client,
                          &modInfo,
                          sizeof(modInfo) );

    if (bEnabled)
    {
        unsigned char pattern[9] = {
            0xF3, 0x0F, 0x11, 0x83, 0x64, 0x09, 0x00, 0x00,  // movss   [rbx+????????], xmm0
            0x40                                             // ??
        };

        godmode_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, pattern);
        godmode_addr ? Patch((char *)godmode_addr, (char *)patch, sizeof(patch)) : (void)NULL;
    }
    else
    {
        unsigned char pattern[8] = {
            0xEB, 0x06,       // jmp    $+0x06
            0x90,             // nop
            0x90,             // nop
            0x90,             // nop
            0x90,             // nop
            0x90,             // nop
            0x90              // nop
        };

        godmode_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, pattern);
        godmode_addr ? Patch((char *)godmode_addr, (char *)original, sizeof(original)) : (void)NULL;
    }

}

void hacks_ToggleOneShot(bool bEnabled)
{
    HANDLE      client;
    MODULEINFO  modInfo;
    uintptr_t   oneshot_addr;

    unsigned char original[16] = {
        0x89, 0x43, 0x78,              // mov   [rbx+78], eax
        0x48, 0x8B, 0x5C, 0x24, 0x30,  // mov   rbx, [rsp+30]
        0x48, 0x83, 0xC4, 0x20,        // add   rsp, 20
        0x5F,                          // pop   rdi
        0xC3,                          // ret 
        0xCC,                          // int3
        0xCC                           // int3
    };

    unsigned char patch[16] = {
        0x31, 0xC0,                    // xor   eax, eax
        0x89, 0x43, 0x78,              // mov   [rbx+78], eax
        0x48, 0x8B, 0x5C, 0x24, 0x30,  // mov   rbx, [rsp+30]
        0x48, 0x83, 0xC4, 0x20,        // add   rsp, 20
        0x5F,                          // pop   rdi
        0xC3                           // ret 
    };


    client = GetModuleHandleA("gamedll_x64_rwdi.dll");
    GetModuleInformation( GetCurrentProcess(),
                          client,
                          &modInfo,
                          sizeof(modInfo) );

    if (bEnabled)
    {
        unsigned char pattern[16] = {
            0x89, 0x43, 0x78,              // mov   [rbx+78], eax
            0x48, 0x8B, 0x5C, 0x24, 0x30,  // mov   rbx, [rsp+30]
            0x48, 0x83, 0xC4, 0x00,        // add   rsp, ??
            0x5F,                          // pop   rdi
            0xC3,                          // ret 
            0x00,                          // int3
            0x00                           // int3
        };

        oneshot_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, pattern);
        oneshot_addr ? Patch((char *)oneshot_addr, (char *)patch, sizeof(patch)) : (void)0;
    }
    else
    {
        unsigned char pattern[16] = {
            0x31, 0xC0,                    // xor   eax, eax
            0x89, 0x43, 0x78,              // mov   [rbx+78], eax
            0x48, 0x8B, 0x5C, 0x24, 0x30,  // mov   rbx, [rsp+30
            0x48, 0x83, 0xC4, 0x00,        // add   rsp, ??
            0x5F,                          // pop   rdi
            0xC3                           // ret 
        };

        oneshot_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, pattern);
        oneshot_addr ? Patch((char *)oneshot_addr, (char *)original, sizeof(original)) : (void)0;
    }

}

void hacks_ToggleInfiniteStamina(bool bEnabled)
{
    HANDLE      client;
    MODULEINFO  modInfo;
    uintptr_t   weapon_addr;
    uintptr_t   sprint_addr;

    //////////////
    // OP CODES //
    //////////////
    
    // Weapon op codes
    unsigned char weapon_original[20] = {
        0xF3, 0x0F, 0x10, 0x4B, 0x10,  // movss     xmm1, [rbx+0x10]
        0xF3, 0x41, 0x0F, 0x5C, 0xC8,  // subss     xmm1, xmm8
        0x0F, 0x2F, 0xCF,              // comiss    xmm1, xmm7
        0x72, 0x0D,                    // jb        gamedll_x64_rwdi.dll+C66C10
        0x0F, 0x2F, 0xC8,              // comiss    xmm1, xmm0
        0x76, 0x05                     // jna       $+0x5
    };
    unsigned char weapon_patch[20] = {
        0xF3, 0x0F, 0x10, 0x4B, 0x10,  // movss     xmm1, [rbx+0x10]
        0xF3, 0x41, 0x0F, 0x5C, 0xC8,  // subss     xmm1, xmm8
        0x0F, 0x2F, 0xCF,              // comiss    xmm1, xmm7
        0x72, 0x0D,                    // jb        gamedll_x64_rwdi.dll+C66C10
        0x0F, 0x2F, 0xC8,              // comiss    xmm1, xmm0
        0x90,                          // nop
        0x90                           // nop
    };

    unsigned char sprint_original[4] = {
        0xF3, 0x0F, 0x5C, 0xC7         // subss     xmm0, xmm7
    }; 
    unsigned char sprint_patch[4] = {
        0xF3, 0x0F, 0x58, 0xC7         // addss     xmm0, xmm7
    }; 

    client = GetModuleHandleA("gamedll_x64_rwdi.dll");
    GetModuleInformation( GetCurrentProcess(),
                          client,
                          &modInfo,
                          sizeof(modInfo) );

    if (bEnabled)
    {
        unsigned char weapon_pattern[18] = {
            0xF3, 0x0F, 0x10, 0x4B, 0x10,  // movss     xmm1, [rbx+0x10]
            0xF3, 0x41, 0x0F, 0x5C, 0xC8,  // subss     xmm1, xmm8
            0x0F, 0x2F, 0xCF,              // comiss    xmm1, xmm7
            0x72, 0x0D,                    // jb        gamedll_x64_rwdi.dll+C66C10
            0x0F, 0x2F, 0xC8,              // comiss    xmm1, xmm0
        };

        weapon_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, weapon_pattern);
        weapon_addr ? Patch((char *)weapon_addr, (char *)weapon_patch, sizeof(weapon_patch)) : (void)0;

        unsigned char sprint_pattern[11] = {
            0xF3, 0x0F, 0x58, 0xC7,        // subss     xmm0, xmm7
            0xF3, 0x0F, 0x11, 0x43, 0x10,  // movss     [rbx+0x10], xmm0
            0x76, 0x0C                     // jna       gamedll_x64_rwdi.dll+C58836
        };

        sprint_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, sprint_pattern);
        sprint_addr ? Patch((char *)sprint_addr, (char *)sprint_patch, sizeof(sprint_patch)) : (void)0;
    }
    else
    {
        unsigned char weapon_pattern[18] = {
            0xF3, 0x0F, 0x10, 0x4B, 0x10,  // movss     xmm1, [rbx+0x10]
            0xF3, 0x41, 0x0F, 0x5C, 0xC8,  // subss     xmm1, xmm8
            0x0F, 0x2F, 0xCF,              // comiss    xmm1, xmm7
            0x72, 0x0D,                    // jb        gamedll_x64_rwdi.dll+C66C10
            0x0F, 0x2F, 0xC8,              // comiss    xmm1, xmm0
        };

        weapon_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, weapon_pattern);
        weapon_addr ? Patch((char *)weapon_addr, (char *)weapon_original, sizeof(weapon_original)) : (void)0;

        unsigned char sprint_pattern[11] = {
            0xF3, 0x0F, 0x58, 0xC7,        // addss     xmm0, xmm7
            0xF3, 0x0F, 0x11, 0x43, 0x10,  // movss     [rbx+0x10], xmm0
            0x76, 0x0C                     // jna       gamedll_x64_rwdi.dll+C58836
        };

        sprint_addr = (uintptr_t)FindSignature(client, modInfo.SizeOfImage, sprint_pattern);
        sprint_addr ? Patch((char *)sprint_addr, (char *)sprint_original, sizeof(sprint_original)) : (void)0;
    }

}
