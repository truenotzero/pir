
#include <Windows.h>

#pragma comment(lib, "user32")

void __declspec(dllexport) foo(void) {
    MessageBoxA(NULL, "this is my text", "this is my caption", MB_OK | MB_ICONINFORMATION);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD fdwReason,
                    LPVOID lpvReserved
) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            foo();
    }

    return TRUE;
}

