// Copyright (c) 2025, Michael Golembewski. All rights reserved.

/**
 * This header file declares helper functions and mappings for Windows message codes.
 */

#pragma once

#include "CoreMinimal.h"

constexpr uint32 WM_USER_START = 0x0400; // Start of user-defined messages
constexpr uint32 WM_USER_END = 0x8000;   // End of user-defined messages
constexpr uint32 WM_APP_START = 0x8000; // Start of application-defined messages
constexpr uint32 WM_APP_END = 0xC000;   // End of application-defined messages

/**
 * Struct representing information about a Windows message.
 */
struct FWindowsMessageInfo
{
    FString Name;        // Name of the message
    FString Description; // Description of the message

    FWindowsMessageInfo() {}
    FWindowsMessageInfo(const FString& InName, const FString& InDesc)
        : Name(InName), Description(InDesc) {}
};

/**
 * Helper class for working with Windows message codes.
 */
class FWindowsMessageCodeHelper
{
public:
    /**
     * Retrieves the name of a Windows message.
     * @param MsgCode - The message code.
     * @return The name of the message.
     */
    static FString GetMessageName(uint32 MsgCode);

    /**
     * Retrieves the description of a Windows message.
     * @param MsgCode - The message code.
     * @return The description of the message.
     */
    static FString GetMessageDescription(uint32 MsgCode);

    /**
     * Retrieves detailed information about a Windows message.
     * @param MsgCode - The message code.
     * @return A struct containing the name and description of the message.
     */
    static FWindowsMessageInfo GetMessageInfo(uint32 MsgCode);

    /**
     * Retrieves the message code by its name.
     * @param MessageName - The name of the message.
     * @return The message code, or 0 if not found.
     */
    static uint32 GetMessageCodeByName(const FString& MessageName);
};
