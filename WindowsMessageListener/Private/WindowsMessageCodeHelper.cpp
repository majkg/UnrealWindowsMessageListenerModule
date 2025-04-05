// Copyright (c) 2025, Michael Golembewski.  All rights reserved.

/**
 * This file provides helper functions and mappings for Windows message codes.
 */

#include "WindowsMessageCodeHelper.h"

namespace {
    constexpr uint32 WM_USER_START = 0x0400;
    constexpr uint32 WM_USER_END = 0x8000;
    constexpr uint32 WM_APP_START = 0x8000;
    constexpr uint32 WM_APP_END = 0xC000;

    FWindowsMessageInfo CreateCustomMessageInfo(uint32 MsgCode, uint32 BaseCode, const TCHAR* BaseName, const TCHAR* Description) {
        return FWindowsMessageInfo(
            FString::Printf(TEXT("%s + 0x%X"), BaseName, MsgCode - BaseCode),
            Description
        );
    }
}

// Define the static map at the global scope
static const TMap<uint32, FWindowsMessageInfo> MessageInfoMap = {
    {0x0000, {TEXT("WM_NULL"), TEXT("No operation.")}},
    {0x0001, {TEXT("WM_CREATE"), TEXT("Sent when a window is being created.")}},
    {0x0002, {TEXT("WM_DESTROY"), TEXT("Sent when a window is being destroyed.")}},
    {0x0003, {TEXT("WM_MOVE"), TEXT("Sent after a window has been moved.")}},
    {0x0005, {TEXT("WM_SIZE"), TEXT("Sent when the size of a window has changed.")}},
    {0x0006, {TEXT("WM_ACTIVATE"), TEXT("Sent when a window is activated or deactivated.")}},
    {0x0007, {TEXT("WM_SETFOCUS"), TEXT("Sent when a window receives keyboard focus.")}},
    {0x0008, {TEXT("WM_KILLFOCUS"), TEXT("Sent when a window loses keyboard focus.")}},
    {0x000A, {TEXT("WM_ENABLE"), TEXT("Sent when a window is enabled or disabled.")}},
    {0x000B, {TEXT("WM_SETREDRAW"), TEXT("Sent to allow changes in a window to be redrawn or not.")}},
    {0x000C, {TEXT("WM_SETTEXT"), TEXT("Sent to set the text of a window.")}},
    {0x000D, {TEXT("WM_GETTEXT"), TEXT("Sent to retrieve the text of a window.")}},
    {0x000E, {TEXT("WM_GETTEXTLENGTH"), TEXT("Sent to retrieve the length of the text in a window.")}},
    {0x0010, {TEXT("WM_CLOSE"), TEXT("Sent as a signal that a window or application should terminate.")}},
    {0x0011, {TEXT("WM_QUERYENDSESSION"), TEXT("Sent when the user chooses to end the session.")}},
    {0x0012, {TEXT("WM_QUIT"), TEXT("Sent to indicate a request to terminate an application.")}},
    {0x0013, {TEXT("WM_QUERYOPEN"), TEXT("Sent to determine whether a minimized window can be restored.")}},
    {0x0014, {TEXT("WM_ERASEBKGND"), TEXT("Sent when the background of a window must be erased.")}},
    {0x0015, {TEXT("WM_SYSCOLORCHANGE"), TEXT("Sent when the system colors change.")}},
    {0x0016, {TEXT("WM_ENDSESSION"), TEXT("Sent when the user session is ending.")}},
    {0x0100, {TEXT("WM_KEYDOWN"), TEXT("Sent when a key is pressed.")}},
    {0x0101, {TEXT("WM_KEYUP"), TEXT("Sent when a key is released.")}},
    {0x0102, {TEXT("WM_CHAR"), TEXT("Sent when a character is typed.")}},
    {0x0103, {TEXT("WM_DEADCHAR"), TEXT("Sent when a dead key is typed.")}},
    {0x0104, {TEXT("WM_SYSKEYDOWN"), TEXT("Sent when a system key is pressed.")}},
    {0x0105, {TEXT("WM_SYSKEYUP"), TEXT("Sent when a system key is released.")}},
    {0x0106, {TEXT("WM_SYSCHAR"), TEXT("Sent when a system character is typed.")}},
    {0x0107, {TEXT("WM_SYSDEADCHAR"), TEXT("Sent when a system dead key is typed.")}},
    {0x0200, {TEXT("WM_MOUSEMOVE"), TEXT("Sent when the mouse is moved.")}},
    {0x0201, {TEXT("WM_LBUTTONDOWN"), TEXT("Sent when the left mouse button is pressed.")}},
    {0x0202, {TEXT("WM_LBUTTONUP"), TEXT("Sent when the left mouse button is released.")}},
    {0x0203, {TEXT("WM_LBUTTONDBLCLK"), TEXT("Sent when the left mouse button is double-clicked.")}},
    {0x0204, {TEXT("WM_RBUTTONDOWN"), TEXT("Sent when the right mouse button is pressed.")}},
    {0x0205, {TEXT("WM_RBUTTONUP"), TEXT("Sent when the right mouse button is released.")}},
    {0x0206, {TEXT("WM_RBUTTONDBLCLK"), TEXT("Sent when the right mouse button is double-clicked.")}},
    {0x0207, {TEXT("WM_MBUTTONDOWN"), TEXT("Sent when the middle mouse button is pressed.")}},
    {0x0208, {TEXT("WM_MBUTTONUP"), TEXT("Sent when the middle mouse button is released.")}},
    {0x0209, {TEXT("WM_MBUTTONDBLCLK"), TEXT("Sent when the middle mouse button is double-clicked.")}},
    {0x020A, {TEXT("WM_MOUSEWHEEL"), TEXT("Sent when the mouse wheel is rotated.")}},
    {0x020B, {TEXT("WM_XBUTTONDOWN"), TEXT("Sent when an X button is pressed.")}},
    {0x020C, {TEXT("WM_XBUTTONUP"), TEXT("Sent when an X button is released.")}},
    {0x020D, {TEXT("WM_XBUTTONDBLCLK"), TEXT("Sent when an X button is double-clicked.")}},
    {0x0210, {TEXT("WM_PARENTNOTIFY"), TEXT("Sent to a parent window when a child window is created or destroyed.")}},
    {0x0211, {TEXT("WM_ENTERMENULOOP"), TEXT("Sent when a menu modal loop is entered.")}},
    {0x0212, {TEXT("WM_EXITMENULOOP"), TEXT("Sent when a menu modal loop is exited.")}},
    {0x0213, {TEXT("WM_NEXTMENU"), TEXT("Sent when the user navigates to the next menu.")}},
    {0x0214, {TEXT("WM_SIZING"), TEXT("Sent when the user is resizing a window.")}},
    {0x0215, {TEXT("WM_CAPTURECHANGED"), TEXT("Sent when the mouse capture changes.")}},
    {0x0216, {TEXT("WM_MOVING"), TEXT("Sent when the user is moving a window.")}},
    {0x0218, {TEXT("WM_POWERBROADCAST"), TEXT("Sent to notify applications of power management events.")}},
    {0x0219, {TEXT("WM_DEVICECHANGE"), TEXT("Sent when a device is added or removed.")}},
    {0x0300, {TEXT("WM_CUT"), TEXT("Sent to cut the current selection to the clipboard.")}},
    {0x0301, {TEXT("WM_COPY"), TEXT("Sent to copy the current selection to the clipboard.")}},
    {0x0302, {TEXT("WM_PASTE"), TEXT("Sent to paste data from the clipboard.")}},
    {0x0303, {TEXT("WM_CLEAR"), TEXT("Sent to clear the current selection.")}},
    {0x0304, {TEXT("WM_UNDO"), TEXT("Sent to undo the last action.")}},
    {0x0400, {TEXT("WM_USER"), TEXT("Base value for user-defined messages.")}},
    {0x8000, {TEXT("WM_APP"), TEXT("Base value for application-defined messages.")}},
};

FWindowsMessageInfo FWindowsMessageCodeHelper::GetMessageInfo(uint32 MsgCode)
{
    if (MsgCode >= ::WM_USER_START && MsgCode < ::WM_USER_END) {
        return CreateCustomMessageInfo(MsgCode, ::WM_USER_START, TEXT("WM_USER"), TEXT("Custom application-defined message (WM_USER)."));
    }

    if (MsgCode >= ::WM_APP_START && MsgCode < ::WM_APP_END) {
        return CreateCustomMessageInfo(MsgCode, ::WM_APP_START, TEXT("WM_APP"), TEXT("Custom application-defined message (WM_APP)."));
    }

    const FWindowsMessageInfo* Found = MessageInfoMap.Find(MsgCode);
    return Found ? *Found : FWindowsMessageInfo(TEXT("Unknown"), TEXT("No description available."));
}

FString FWindowsMessageCodeHelper::GetMessageName(uint32 MsgCode)
{
    return GetMessageInfo(MsgCode).Name;
}

FString FWindowsMessageCodeHelper::GetMessageDescription(uint32 MsgCode)
{
    return GetMessageInfo(MsgCode).Description;
}

uint32 FWindowsMessageCodeHelper::GetMessageCodeByName(const FString& MessageName)
{
    for (const auto& Pair : MessageInfoMap)
    {
        if (Pair.Value.Name.Equals(MessageName, ESearchCase::IgnoreCase))
        {
            return Pair.Key;
        }
    }
    return 0; // Return 0 if the message name is not found
}
