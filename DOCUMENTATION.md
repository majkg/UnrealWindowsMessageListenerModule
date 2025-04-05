# Documentation

## Overview
The `WindowsMessageListener` module is designed to handle Windows messages in Unreal Engine projects. It provides a flexible API for processing, filtering, and managing Windows messages. This module is useful for integrating custom hardware, handling system-level events, and implementing advanced user interactions.

## Classes

### FWindowsMessageListener
- **Description**: Handles Windows messages and forwards them to registered message processors.
- **Key Methods**:
  - `StartListening()`: Starts the message listener.
  - `StopListening()`: Stops the message listener.
  - `AddMessageHandler(IWindowsMessageHandler* handler)`: Adds a message handler.
  - `RemoveMessageHandler(IWindowsMessageHandler* handler)`: Removes a message handler.
  - `IsMessageAllowed(uint32 MsgCode) const`: Checks if a message type is allowed.

#### Examples

##### Starting the Listener
```cpp
FWindowsMessageListener Listener;
Listener.StartListening(); // Begin listening for Windows messages
UE_LOG(LogTemp, Log, TEXT("Listener started.")); // Log that the listener has started
```

##### Stopping the Listener
```cpp
Listener.StopListening(); // Stop listening for Windows messages
UE_LOG(LogTemp, Log, TEXT("Listener stopped.")); // Log that the listener has stopped
```

##### Adding a Message Handler
```cpp
class FMyCustomHandler : public IWindowsMessageHandler
{
public:
    virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override
    {
        UE_LOG(LogTemp, Log, TEXT("Message received: %u"), msg); // Log the received message
        return true; // Indicate the message was handled
    }
};

FMyCustomHandler* MyHandler = new FMyCustomHandler();
Listener.AddMessageHandler(MyHandler); // Add the custom message handler to the listener
```

##### Removing a Message Handler
```cpp
Listener.RemoveMessageHandler(MyHandler); // Remove the custom message handler from the listener
delete MyHandler; // Clean up the handler to avoid memory leaks
```

##### Filtering Messages
```cpp
Listener.AddAllowedMessageType(WM_KEYDOWN); // Allow the WM_KEYDOWN message type
Listener.AddAllowedMessageType(WM_KEYUP);   // Allow the WM_KEYUP message type
if (Listener.IsMessageAllowed(WM_KEYDOWN))
{
    UE_LOG(LogTemp, Log, TEXT("WM_KEYDOWN is allowed.")); // Log that WM_KEYDOWN is allowed
}
```

### FWindowsMessageCodeHelper
- **Description**: Provides helper functions for working with Windows message codes.
- **Key Methods**:
  - `GetMessageName(uint32 MsgCode)`: Retrieves the name of a Windows message.
  - `GetMessageDescription(uint32 MsgCode)`: Retrieves the description of a Windows message.

#### Examples

##### Getting the Name of a Message
```cpp
uint32 MsgCode = WM_KEYDOWN; // Define the message code to query
FString MsgName = FWindowsMessageCodeHelper::GetMessageName(MsgCode); // Get the name of the message
UE_LOG(LogTemp, Log, TEXT("Message Name: %s"), *MsgName); // Log the message name
```

##### Getting the Description of a Message
```cpp
uint32 MsgCode = WM_KEYDOWN; // Define the message code to query
FString MsgDescription = FWindowsMessageCodeHelper::GetMessageDescription(MsgCode); // Get the description of the message
UE_LOG(LogTemp, Log, TEXT("Message Description: %s"), *MsgDescription); // Log the message description
```

## Setup
1. Include the `WindowsMessageListener` module in your project's build file.
2. Add the necessary headers to your source files.

## Examples

### Starting the Listener
```cpp
FWindowsMessageListener Listener;
Listener.StartListening(); // Begin listening for Windows messages
```

### Adding a Message Handler
```cpp
Listener.AddMessageHandler(MyCustomHandler); // Add a custom message handler to process messages
```

### Filtering Messages
```cpp
Listener.AddAllowedMessageType(WM_KEYDOWN); // Allow the WM_KEYDOWN message type
```

## License
This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
