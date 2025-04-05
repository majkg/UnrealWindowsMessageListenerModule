#include "Misc/AutomationTest.h"
#include "WindowsMessageListener.h"
#include "WindowsMessageCodeHelper.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWindowsMessageListenerTest, "WindowsMessageListener.BasicFunctionality", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FWindowsMessageListenerTest::RunTest(const FString& Parameters)
{
    FWindowsMessageListener Listener;

    // Test StartListening and StopListening in various states
    TestFalse("Listener should not be active initially", Listener.IsListening());
    Listener.StartListening();
    TestTrue("Listener should be active after StartListening", Listener.IsListening());
    Listener.StartListening(); // Call again to ensure idempotence
    TestTrue("Listener should remain active after repeated StartListening", Listener.IsListening());
    Listener.StopListening();
    TestFalse("Listener should not be active after StopListening", Listener.IsListening());
    Listener.StopListening(); // Call again to ensure idempotence
    TestFalse("Listener should remain inactive after repeated StopListening", Listener.IsListening());

    // Test AddAllowedMessageType and IsMessageAllowed
    Listener.AddAllowedMessageType(WM_KEYDOWN);
    TestTrue("WM_KEYDOWN should be allowed", Listener.IsMessageAllowed(WM_KEYDOWN));

    Listener.RemoveAllowedMessageType(WM_KEYDOWN);
    TestFalse("WM_KEYDOWN should not be allowed after removal", Listener.IsMessageAllowed(WM_KEYDOWN));

    // Test invalid message type handling
    TestFalse("Invalid message type should not be allowed", Listener.IsMessageAllowed(-1));

    // Test adding duplicate message types
    Listener.AddAllowedMessageType(WM_KEYDOWN);
    Listener.AddAllowedMessageType(WM_KEYDOWN); // Add duplicate
    TestTrue("WM_KEYDOWN should still be allowed after adding duplicate", Listener.IsMessageAllowed(WM_KEYDOWN));

    // Test verbose logging toggle
    Listener.SetVerboseLoggingEnabled(true);
    TestTrue("Verbose logging should be enabled", Listener.IsVerboseLoggingEnabled());

    Listener.SetVerboseLoggingEnabled(false);
    TestFalse("Verbose logging should be disabled", Listener.IsVerboseLoggingEnabled());

    Listener.SetVerboseLoggingEnabled(true);
    TestTrue("Verbose logging should be re-enabled", Listener.IsVerboseLoggingEnabled());

    // Test clearing all allowed message types
    Listener.AddAllowedMessageType(WM_KEYDOWN);
    Listener.AddAllowedMessageType(WM_KEYUP);
    Listener.ClearAllowedMessageTypes();
    TestFalse("WM_KEYDOWN should not be allowed after clearing", Listener.IsMessageAllowed(WM_KEYDOWN));
    TestFalse("WM_KEYUP should not be allowed after clearing", Listener.IsMessageAllowed(WM_KEYUP));

    // Test IsMessageAllowed with no allowed messages
    TestFalse("No message should be allowed initially", Listener.IsMessageAllowed(WM_KEYUP));

    // Test SetVerboseLoggingEnabled and IsVerboseLoggingEnabled
    Listener.SetVerboseLoggingEnabled(true);
    TestTrue("Verbose logging should be enabled", Listener.IsVerboseLoggingEnabled());
    Listener.SetVerboseLoggingEnabled(false);
    TestFalse("Verbose logging should be disabled", Listener.IsVerboseLoggingEnabled());

    return true;
}