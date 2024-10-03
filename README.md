# UAC Bypass Tool

**A tool to bypass User Account Control (UAC) by manipulating the Windows registry and executing `fodhelper.exe`.**

This tool leverages a known UAC bypass technique by modifying the Windows registry and launching `fodhelper.exe` to run commands or executables with elevated privileges, bypassing UAC prompts.

## Features:
- **Registry Manipulation**: The tool modifies the `HKEY_CURRENT_USER\Software\Classes\ms-settings\Shell\Open\command` registry key to insert a custom command or executable.
- **UAC Bypass**: It sets the `DelegateExecute` value to an empty string, allowing the tool to bypass the UAC prompt.
- **Elevated Execution**: After modifying the registry, the tool launches `fodhelper.exe`, which triggers the execution of the specified command or executable with elevated privileges.
- **Error Handling**: Includes basic error handling for registry operations and process execution.

## Usage:
```bash
UacBypass.exe <file.exe or command>
```
