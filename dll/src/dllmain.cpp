//
// Created by user on 1/18/2023.
//

#include "game/sdk.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>

DWORD WINAPI hackThread(HMODULE hModule)
{
    FILE* file{ nullptr };
    if (AllocConsole())
    {
        freopen_s(&file, "CONOUT$", "w", stdout);
    }

    std::cout << "Test string\n";

    // replace client.dll below to client_panorama.dll if -insecure is not set
    // take your own risk if you got banned
    auto clientEntityList{
            reinterpret_cast<IClientEntityList*>(
                    getInterface("client.dll", "VClientEntityList003")) };

    auto baseClientDll{
            reinterpret_cast<IBaseClientDLL*>(
                    getInterface("client.dll", "VClient018")) };

    while (!(GetAsyncKeyState(VK_END) & 1))
    {
        auto clientClasses{ baseClientDll->GetAllClasses() };

        auto healthOffset{ getNetVarOffset(clientClasses, "DT_BasePlayer", "m_iHealth") };

        auto theEntityNum2{ reinterpret_cast<uintptr_t>(clientEntityList->GetClientEntity(2)) };

        auto& healthValueOfTheEntityNum2{ *reinterpret_cast<int*>(theEntityNum2 + healthOffset) };

        std::cout << "Health is " << healthValueOfTheEntityNum2 << '\n';
    }

    std::fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HMODULE hModule,  // handle to DLL module
        DWORD fdwReason,     // reason for calling function
        LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        CloseHandle(CreateThread(nullptr,
                0,
                reinterpret_cast<LPTHREAD_START_ROUTINE>(hackThread),
                hModule,
                0,
                nullptr));
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
