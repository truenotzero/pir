# Process Injection Research (PIR)
Researching different ways to do process injection

## CreateRemoteThread
This way of process injection has been extensively documented and is easily countered
What I propose: Instead of using Win32 or NTApi, directly use the kernel syscalls

Step 1: Converting from Win32API to NTApi calls
Step 2: Converting the NTApi calls to raw syscalls

Step 1:
LoadLibraryA => KERNELBASE!LoadLibraryExW: KERNELBASE!__imp_LdrGetDllPath, KERNELBASE!__imp_LdrLoadDll

