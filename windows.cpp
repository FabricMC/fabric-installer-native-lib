#include "MojangLauncherHelper.h"

#include <windows.h>

// Include after Windows.h
#include <wil/resource.h>

constexpr LPCWSTR MinecraftLauncherMutexName = L"MojangLauncher";

JNIEXPORT jboolean JNICALL
Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isMojangLauncherOpen(
    JNIEnv*, jclass) {
    wil::unique_handle handle{ ::OpenMutexW(0, false, MinecraftLauncherMutexName) };

    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
        return 0;
    }

    return 1;
}