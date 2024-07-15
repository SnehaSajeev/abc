#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a command to list installed programs with version information
    char command[] = "powershell -ExecutionPolicy Bypass -Command Get-WmiObject Win32_Product | Format-Table Name, Version";

    // Create the child process
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        printf("Error creating process: %d\n", GetLastError());
        return 1;
    }

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process handles
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    printf("Installed applications and versions:\n");

    // You can now read the output from the child process (standard output)
    // to display the list of applications and versions.
    // Implement logic to handle the output stream and parse the information.

    return 0;
}

Explanation:

Include Headers: stdio.h for standard input/output and windows.h for Win32 API functions.
Process Structures: STARTUPINFO and PROCESS_INFORMATION structures are declared for launching the child process.
Initialize Structures: ZeroMemory is used to initialize the structures to avoid potential issues with uninitialized values.
PowerShell Command: The command string holds the PowerShell command to execute:
powershell: Launches the PowerShell interpreter.
-ExecutionPolicy Bypass: Temporarily allows execution of unsigned scripts (replace if needed).
Get-WmiObject Win32_Product: Retrieves information about installed software using WMI (Windows Management Instrumentation).
Format-Table Name, Version: Formats the output to display Name and Version columns.
Create Process: CreateProcess initiates a new child process to execute the PowerShell command.
Error Handling: If creating the process fails, an error message is printed using GetLastError.
Wait for Completion: WaitForSingleObject waits indefinitely for the child process (PowerShell) to finish.
Close Handles: CloseHandle closes the process thread and process handles to avoid resource leaks.
Output Handling: A placeholder comment indicates the section for handling the child process output (standard output stream) to extract application names and versions. You'll need to implement logic to read the output stream and parse the data using functions like ReadConsoleOutputCharacter or ReadFile.
Remember to compile this code with the appropriate compiler flags (e.g., -mwindows for GCC) and link with the necessary libraries (e.g., user32.lib and kernel32.lib).

By utilizing PowerShell, this approach offers a more reliable and standardized way to retrieve installed application information in Windows environments.
