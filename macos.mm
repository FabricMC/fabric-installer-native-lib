#include <AppKit/NSRunningApplication.h>
#include "MojangLauncherHelper.h"

NSString *const MinecraftLauncherBundleIdentifier = @"com.mojang.minecraftlauncher";

jboolean Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isMojangLauncherOpen(JNIEnv *, jclass)
{
    for (NSRunningApplication *app in[[NSWorkspace sharedWorkspace] runningApplications])
    {
        if ([[app bundleIdentifier]  isEqual: MinecraftLauncherBundleIdentifier])
        {
            return 1;
        }
    }

    return 0;
}

jboolean Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isLikelyOnline(JNIEnv *, jclass)
{
    // TODO
    return 1;
}