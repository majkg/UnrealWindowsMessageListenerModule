// Copyright (c) 2025, Michael Golembewski.  All rights reserved.

/**
 * This file contains the implementation of the WindowsMessageListener module.
 * It handles the startup and shutdown of the module.
 */

#include "WindowsMessageListener.h"
#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogWindowsMessageListener, Log, All);

class WINDOWSMESSAGELISTENER_API FWindowsMessageListenerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        UE_LOG(LogWindowsMessageListener, Log, TEXT("WindowsMessageListener module started."));
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogWindowsMessageListener, Log, TEXT("WindowsMessageListener module shut down."));
    }
};

IMPLEMENT_MODULE(FWindowsMessageListenerModule, WindowsMessageListener);