// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

/*
All credited to @thepj120 (https://www.unknowncheats.me/forum/members/357301.html) and @JWilson (https://www.unknowncheats.me/forum/members/3083088.html) for creating source code.

push rbx
sub  rsp, 0x20
mov rax, 0xDEADCAFEBEEFCAFE
call rax
lea  rdx, [rsp + 0x28]
mov  rbx, rax
mov  rax, qword ptr [rdx + 0x30]
mov  rcx, rax
mov  rax, 0xDEADCAFEBEEFCAFE
sub  rcx, rax
cmp  rcx, 0xE05241
jne  end
mov  rax, qword ptr [rdx + 0x30]
lea  rcx, [rax + 0x68]
mov  qword ptr [rdx + 0x30], rcx
mov  rax, rdi
mov  byte ptr [rax + 0x52], 0
mov  rax, rdi
mov  byte ptr [rax + 0x51], 0
end:
mov  rax, rbx
add  rsp, 0x20
pop  rbx
ret
*/

unsigned char UnlockAllShellcode[89] = {
    0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0xB8, 0xFE, 0xCA, 0xEF, 0xBE, 0xFE,
    0xCA, 0xAD, 0xDE, 0xFF, 0xD0, 0x48, 0x8D, 0x54, 0x24, 0x28, 0x48, 0x89,
    0xC3, 0x48, 0x8B, 0x42, 0x30, 0x48, 0x89, 0xC1, 0x48, 0xB8, 0xFE, 0xCA,
    0xEF, 0xBE, 0xFE, 0xCA, 0xAD, 0xDE, 0x48, 0x29, 0xC1, 0x48, 0x81, 0xF9,
    0x41, 0x52, 0xE0, 0x00, 0x75, 0x1A, 0x48, 0x8B, 0x42, 0x30, 0x48, 0x8D,
    0x48, 0x68, 0x48, 0x89, 0x4A, 0x30, 0x48, 0x89, 0xF8, 0xC6, 0x40, 0x52,
    0x00, 0x48, 0x89, 0xF8, 0xC6, 0x40, 0x51, 0x00, 0x48, 0x89, 0xD8, 0x48,
    0x83, 0xC4, 0x20, 0x5B, 0xC3
};

void EnablePatchLessUnlockAll()
{
    unsigned __int64 GameBaseAddress = (unsigned __int64)GetModuleHandleA(NULL);

    PVOID AllocatedMemory = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    *(unsigned long long*)(&UnlockAllShellcode[0x7]) = *(unsigned __int64*)(GameBaseAddress + 0x5AD5130);
    *(unsigned long long*)(&UnlockAllShellcode[0x22]) = GameBaseAddress;

    memcpy(AllocatedMemory, UnlockAllShellcode, sizeof(UnlockAllShellcode));

    *(unsigned __int64*)(GameBaseAddress + 0x5AD5130) = (unsigned __int64)AllocatedMemory;
};




//Create DLL and making case if attach/detach
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        EnablePatchLessUnlockAll();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

