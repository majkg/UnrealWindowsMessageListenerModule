// Copyright (c) 2025, Michael Golembewski. All rights reserved.

/**
 * This header file declares the FWindowsMessageListener class, which handles Windows messages.
 */

#pragma once

#include "CoreMinimal.h"
#include "Windows/WindowsApplication.h"
#include "Framework/Application/SlateApplication.h"

/**
 * FWindowsMessageListener
 * Handles Windows messages and forwards them to registered message processors.
 */
class WINDOWSMESSAGELISTENER_API FWindowsMessageListener : public IWindowsMessageHandler
{
public:
    FWindowsMessageListener();
    virtual ~FWindowsMessageListener();

    /**
     * Processes a Windows message.
     * @param hwnd - Handle to the window.
     * @param msg - The message identifier.
     * @param wParam - Additional message information.
     * @param lParam - Additional message information.
     * @param outResult - The result of the message processing.
     * @return True if the message was handled.
     */
    virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& outResult) override;

    /**
     * Determines whether a message should be processed.
     * @param hwnd - Handle to the window.
     * @param msg - The message identifier.
     * @return True if the message should be processed.
     */
    virtual bool ShouldProcessMessage(HWND hwnd, uint32 msg) const;

    /**
     * Adds a message handler to handle messages.
     * @param handler - The message handler to add.
     */
    void AddMessageHandler(IWindowsMessageHandler* handler);

    /**
     * Removes a message handler.
     * @param handler - The message handler to remove.
     */
    void RemoveMessageHandler(IWindowsMessageHandler* handler);

    /**
     * Removes all message handlers.
     */
    void RemoveAllMessageHandlers();

    /**
     * Starts the message listener.
     * Use this to begin processing Windows messages.
     */
    void StartListening();

    /**
     * Stops the message listener.
     * Use this to stop processing Windows messages.
     */
    void StopListening();

    /**
     * Checks if the listener is currently active.
     * @return True if the listener is active.
     */
    bool IsListening() const;

    /**
     * Adds a message type to the allowed list.
     * @param MsgCode - The message code to allow.
     */
    void AddAllowedMessageType(uint32 MsgCode);

    /**
     * Removes a message type from the allowed list.
     * @param MsgCode - The message code to disallow.
     */
    void RemoveAllowedMessageType(uint32 MsgCode);

    /**
     * Clears all allowed message types.
     */
    void ClearAllowedMessageTypes();

    /**
     * Checks if a message type is allowed.
     * @param MsgCode - The message code to check.
     * @return True if the message type is allowed.
     */
    bool IsMessageAllowed(uint32 MsgCode) const;

    /**
     * Enables or disables verbose logging for debugging purposes.
     * @param bEnabled - True to enable verbose logging, false to disable.
     */
    void SetVerboseLoggingEnabled(bool bEnabled);

    /**
     * Checks if verbose logging is enabled.
     * @return True if verbose logging is enabled.
     */
    bool IsVerboseLoggingEnabled() const;

protected:

    /**
     * Retrieves the FWindowsApplication instance if available.
     * @return A pointer to the FWindowsApplication instance, or nullptr if unavailable.
     */
    FWindowsApplication* GetApplication() const;

private:

    TArray<IWindowsMessageHandler*> MessageHandlers; // List of registered message handlers
    bool bIsListening = false;                      // Tracks whether the listener is active
    TSet<uint32> AllowedMessageTypes;               // Set of allowed message types
    bool bEnableVerboseLogging = false;             // Debug flag to control verbose logging

    /**
     * Logs detailed information about a Windows message for debugging purposes.
     * @param hwnd - Handle to the window.
     * @param msg - The message identifier.
     * @param Context - Contextual information for the log.
     */
    void LogMessageDetails(HWND hwnd, uint32 msg, const TCHAR* Context) const;
};