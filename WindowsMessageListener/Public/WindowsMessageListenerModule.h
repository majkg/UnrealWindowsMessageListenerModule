// Copyright (c) 2025, Michael Golembewski. All rights reserved.

/**
 * This header file declares the FWindowsMessageListenerModule class, which manages the module lifecycle.
 */

#pragma once

#include "Modules/ModuleManager.h"

/**
 * FWindowsMessageListenerModule
 * Handles the startup and shutdown of the WindowsMessageListener module.
 */
class FWindowsMessageListenerModule : public IModuleInterface
{
public:
    /**
     * Called when the module is starting up.
     * Use this to initialize resources or register components.
     */
    virtual void StartupModule() override;

    /**
     * Called when the module is shutting down.
     * Use this to clean up resources or unregister components.
     */
    virtual void ShutdownModule() override;
};