#include "MojangLauncherHelper.h"

#include <windows.h>

constexpr LPCWSTR MinecraftLauncherMutexName = L"MojangLauncher";

JNIEXPORT jboolean JNICALL Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isMojangLauncherOpen(JNIEnv *, jclass) {
    HANDLE handle = OpenMutexW(0, false, MinecraftLauncherMutexName);

    if (GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        return 0;
    }

    if (handle != nullptr)
    {
        CloseHandle(handle);
    }

    return 1;
}