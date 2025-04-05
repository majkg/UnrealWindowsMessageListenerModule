// Copyright (c) 2025, Michael Golembewski.  All rights reserved.

/**
 * This file implements the FWindowsMessageListener class, which processes and forwards Windows messages.
 */

#include "WindowsMessageListener.h"
#include "WindowsMessageCodeHelper.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogWindowsMessageListener, Log, All);

FWindowsMessageListener::FWindowsMessageListener()
{
    UE_LOG(LogWindowsMessageListener, Log, TEXT("FWindowsMessageListener constructed."));
}

// Ensure proper cleanup in the destructor
FWindowsMessageListener::~FWindowsMessageListener()
{
    StopListening(); // Ensure the listener is stopped
    RemoveAllMessageHandlers(); // Clear all handlers
    ClearAllowedMessageTypes(); // Clear allowed message types
    UE_LOG(LogWindowsMessageListener, Log, TEXT("FWindowsMessageListener destructed and cleaned up."));
}

// Helper function for verbose logging
void FWindowsMessageListener::LogMessageDetails(HWND hwnd, uint32 msg, const TCHAR* Context) const
{
    if (bEnableVerboseLogging)
    {
        FString MessageName = FWindowsMessageCodeHelper::GetMessageName(msg);
        FString MessageDescription = FWindowsMessageCodeHelper::GetMessageDescription(msg);
        UE_LOG(LogWindowsMessageListener, VeryVerbose, TEXT("%s: hwnd=%p, msg=%u, name=%s, description=%s"), Context, hwnd, msg, *MessageName, *MessageDescription);
    }
}

WINDOWSMESSAGELISTENER_API bool FWindowsMessageListener::ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32 &outResult)
{
    if (bEnableVerboseLogging)
    {
        LogMessageDetails(hwnd, msg, TEXT("Processing message"));
    }

    if (!ShouldProcessMessage(hwnd, msg))
    {
        if (bEnableVerboseLogging)
        {
            UE_LOG(LogWindowsMessageListener, VeryVerbose, TEXT("Message ignored: hwnd=%p, msg=%u"), hwnd, msg);
        }
        return false;
    }

    for (IWindowsMessageHandler *handler : MessageHandlers)
    {
        if (handler && handler != this && ShouldProcessMessage(hwnd, msg))
        {
            LogMessageDetails(hwnd, msg, TEXT("Forwarding message to handler"));
            handler->ProcessMessage(hwnd, msg, wParam, lParam, outResult);
        }
    }

    return false;
}

WINDOWSMESSAGELISTENER_API bool FWindowsMessageListener::ShouldProcessMessage(HWND hwnd, uint32 msg) const
{
    if (bEnableVerboseLogging)
    {
        UE_LOG(LogWindowsMessageListener, Verbose, TEXT("Checking if message should be processed: hwnd=%p, msg=%u"), hwnd, msg);
    }
    return IsMessageAllowed(msg);
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::AddMessageHandler(IWindowsMessageHandler *handler)
{
    if (handler)
    {
        MessageHandlers.Add(handler);
        UE_LOG(LogWindowsMessageListener, Log, TEXT("Message handler added: %p"), handler);
    }
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::RemoveMessageHandler(IWindowsMessageHandler *handler)
{
    if (handler)
    {
        MessageHandlers.Remove(handler);
        UE_LOG(LogWindowsMessageListener, Log, TEXT("Message handler removed: %p"), handler);
    }
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::RemoveAllMessageHandlers()
{
    MessageHandlers.Empty();
    UE_LOG(LogWindowsMessageListener, Log, TEXT("All message handlers removed."));
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::StartListening()
{
    if (!bIsListening)
    {
        FWindowsApplication *WindowsApplication = GetApplication();
        if (WindowsApplication)
        {
            WindowsApplication->AddMessageHandler(*this);
            bIsListening = true;
            UE_LOG(LogWindowsMessageListener, Log, TEXT("Message listener started and registered with FWindowsApplication."));
        }
        else
        {
            UE_LOG(LogWindowsMessageListener, Error, TEXT("Failed to get FWindowsApplication instance."));
        }
    }
    else
    {
        UE_LOG(LogWindowsMessageListener, Warning, TEXT("Message listener is already active."));
    }
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::StopListening()
{
    if (bIsListening)
    {
        FWindowsApplication *WindowsApplication = GetApplication();
        if (WindowsApplication)
        {
            WindowsApplication->RemoveMessageHandler(*this);
        }
        bIsListening = false;
        UE_LOG(LogWindowsMessageListener, Log, TEXT("Message listener stopped and unregistered from FWindowsApplication."));
    }
    else
    {
        UE_LOG(LogWindowsMessageListener, Warning, TEXT("Message listener is not active."));
    }
}

WINDOWSMESSAGELISTENER_API bool FWindowsMessageListener::IsListening() const
{
    return bIsListening;
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::AddAllowedMessageType(uint32 MsgCode)
{
    AllowedMessageTypes.Add(MsgCode);
    UE_LOG(LogWindowsMessageListener, Log, TEXT("Added allowed message type: %u"), MsgCode);
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::RemoveAllowedMessageType(uint32 MsgCode)
{
    AllowedMessageTypes.Remove(MsgCode);
    UE_LOG(LogWindowsMessageListener, Log, TEXT("Removed allowed message type: %u"), MsgCode);
}

WINDOWSMESSAGELISTENER_API void FWindowsMessageListener::ClearAllowedMessageTypes()
{
    AllowedMessageTypes.Empty();
    UE_LOG(LogWindowsMessageListener, Log, TEXT("Cleared all allowed message types."));
}

// Clarify default behavior when AllowedMessageTypes is empty
WINDOWSMESSAGELISTENER_API bool FWindowsMessageListener::IsMessageAllowed(uint32 MsgCode) const
{
    if (AllowedMessageTypes.Num() == 0) // If no messages are allowed, block all
    {
        // Default behavior: Block all messages if no allowed types are specified.
        return false;
    }
    return AllowedMessageTypes.Contains(MsgCode);
}

void FWindowsMessageListener::SetVerboseLoggingEnabled(bool bEnabled)
{
    bEnableVerboseLogging = bEnabled;
    UE_LOG(LogWindowsMessageListener, Log, TEXT("Verbose logging %s"), bEnabled ? TEXT("enabled") : TEXT("disabled"));
}

WINDOWSMESSAGELISTENER_API bool FWindowsMessageListener::IsVerboseLoggingEnabled() const
{
    return bEnableVerboseLogging;
}

FWindowsApplication *FWindowsMessageListener::GetApplication() const
{
    if (FSlateApplication::IsInitialized())
    {
        return (FWindowsApplication *)FSlateApplication::Get().GetPlatformApplication().Get();
    }
    return nullptr;
}