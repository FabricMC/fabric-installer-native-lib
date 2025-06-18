#include "MojangLauncherHelper.h"

#include <windows.h>
#include <netlistmgr.h>

// Include after Windows.h
#include <wil/com.h>
#include <wil/resource.h>

constexpr LPCWSTR MinecraftLauncherMutexName = L"MojangLauncher";

JNIEXPORT jboolean JNICALL
Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isMojangLauncherOpen(
    JNIEnv*, jclass) {
    wil::unique_handle handle{ ::OpenMutexW(0, false, MinecraftLauncherMutexName) };

    if (::GetLastError() == ERROR_FILE_NOT_FOUND) {
        return 0;
    }

    return 1;
}

JNIEXPORT jboolean JNICALL
Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isLikelyOnline(
    JNIEnv*, jclass) {
    try {
        auto coInit = wil::CoInitializeEx();

        auto networkListManager =
            wil::CoCreateInstance<INetworkListManager>(CLSID_NetworkListManager);

        NLM_CONNECTIVITY connectivity{ NLM_CONNECTIVITY_DISCONNECTED };
        THROW_IF_FAILED(networkListManager->GetConnectivity(&connectivity));

        return connectivity != NLM_CONNECTIVITY_DISCONNECTED;
    }
    catch (const wil::ResultException&) {
        // Failed to to determine connectivity, assume online
        return JNI_TRUE;
    }
}