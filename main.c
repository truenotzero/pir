
#include "methods.h"
#include <stdio.h>

FARPROC GetNtProc(LPCSTR nt_proc_name) {
  HMODULE ntdll = GetModuleHandle("ntdll");
  if (!ntdll) {
    return NULL;
  }

  FARPROC proc = GetProcAddress(ntdll, nt_proc_name);
  if (!proc) {
    return NULL;
  }

  return proc;
}

int GetSSN(LPCSTR nt_proc_name) {
  static int const LIMIT = 0x50;

  FARPROC proc = GetNtProc(nt_proc_name);
  if (!proc) { return -1; }

  // find pattern:
  // 4c 8b d1         mov r10, rcx
  // b8 ?? ?? ?? ??   mov eax, ??

  char const *prelude = "\x4C\x8B\xD1\xB8";
  char const *it;
  int aborted;
  for (it = (char *)proc; it < (char *)proc + LIMIT; ++it) {
    aborted = 0;
    for (char const *jt = prelude; *jt; ++jt) {
      if (*it == *jt) {
        ++it;
      } else {
        aborted = 1;
        break;
      }
    }

    if (!aborted) {
      break;
    }
  }

  // LIMIT was reached
  if (aborted) { return -1; }

  return *(int *)it;
}

typedef LONG NtCreateThreadEx_t(
    PHANDLE ThreadHandle,
    ACCESS_MASK DesiredAccess,
    void *ObjectAttributes,
    HANDLE ProcessHandle,
    void *StartRoutine,
    PVOID Argument,
    ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
    SIZE_T ZeroBits,
    SIZE_T StackSize,
    SIZE_T MaximumStackSize,
    void *AttributeList
);

NtCreateThreadEx_t NtCreateThreadEx;

#pragma comment(lib, "user32")
void hello() {
    MessageBoxA(NULL, "it works", "oh yeah", MB_OK | MB_ICONINFORMATION);
}

// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // HANDLE handle;
    // NtCreateThreadEx(&handle, THREAD_ALL_ACCESS, NULL, GetCurrentProcess(), &hello, NULL, 0, 0, 0, 0, NULL);
    // // handle = CreateThread(0, 0, (void *) &hello, 0, 0, 0);
    // WaitForSingleObject(handle, -1);
    // CloseHandle(handle);

    // printf("Acquire SSN Tool\nEnter the NT function name and press <ENTER>\n\n");
    // #define BUFSIZE 256
    // char buffer[BUFSIZE];
    // while (gets_s(buffer, BUFSIZE)) {
    //     int ssn = GetSSN(buffer);
    //     printf("SSN for ntdll!%s: %d\n", buffer, ssn);
    // }

    // return 0;
// }

int main(int argc, char *argv[]) {
    printf("Acquire SSN Tool\nEnter the NT function name and press <ENTER>\n\n");
    #define BUFSIZE 256
    char buffer[BUFSIZE];
    while (gets_s(buffer, BUFSIZE)) {
        int ssn = GetSSN(buffer);
        if (ssn != -1) {
            printf("SSN for ntdll!%s: 0%02Xh\n", buffer, ssn);
        } else {
            printf("Failed to acquire SSN for: %s...\n", buffer);
        }
    }

    return 0;
}
