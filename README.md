# WindowsMessageListener Module

This module provides functionality for handling Windows messages in Unreal Engine projects. It includes tools for processing, filtering, and managing Windows messages efficiently.

## Introduction
The `WindowsMessageListener` module is ideal for developers who need to interact with low-level Windows messages in their Unreal Engine projects. It is useful for:
- Integrating custom hardware or input devices.
- Handling system-level events such as power state changes or device connections.
- Implementing advanced user interactions that require direct access to Windows messages.
- Debugging and monitoring Windows messages for development purposes.

## Features

### Process Windows Messages
The module allows you to intercept and process Windows messages directly within your Unreal Engine project. This is useful when integrating custom input devices, handling system-level events, or implementing advanced user interactions.

### Dynamic Message Handlers
You can dynamically add or remove message handlers at runtime. This enables you to customize the behavior of your application based on specific requirements or user interactions.

### Message Filtering
The module provides filtering capabilities, allowing you to specify which types of Windows messages should be processed. This ensures that only relevant messages are handled, improving performance and reducing unnecessary processing.

### Verbose Logging
When debugging, message logs can easily get spammed when dealing with verbose message data, so verbose logging can be toggled at runtime. This feature provides on-demnand logging for detailed information about the messages being processed, letting you identify and resolve issues more efficiently.

### Modular Design
The module is designed to be modular and easy to integrate into existing Unreal Engine projects.

## Installation

### Adding to a Module's Source Code
1. Copy the `WindowsMessageListener` folder into the `Source` directory of your module.
2. Open the `.Build.cs` file of your module.
3. Add `"WindowsMessageListener"` to the `PublicDependencyModuleNames` array. For example:
   ```csharp
   PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "WindowsMessageListener" });
   ```
4. Include the necessary headers in your module's source files to access the module's functionality.

### In the Main Project
1. Copy the `WindowsMessageListener` folder into your Unreal Engine project's `Source` directory.
2. Add `WindowsMessageListener` to the `PublicDependencyModuleNames` array in your project's `.Build.cs` file.
3. Include the necessary headers in your source files.

### Adding the Module to Source Code
To use the `WindowsMessageListener` module in your project or module:
1. Open the `.Build.cs` file of your project or module.
2. Add `"WindowsMessageListener"` to the `PublicDependencyModuleNames` array. For example:
   ```csharp
   PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "WindowsMessageListener" });
   ```
3. Include the necessary headers in your source files to access the module's functionality.

## Usage
- Use the `FWindowsMessageListener` class to start and stop listening for Windows messages.
- Add custom message handlers to process specific messages.


### About the Author
I'm Michael Golembewski, an independent designer and developer who enjoys working with Unreal Engine.  This module is one that I've used in a few recent projects, so I thought I'd share.

## License
This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
