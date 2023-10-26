#include <Windows.h>
#include <string>
#include <time.h>

// Идентификаторы элементов управления
#define BTN_CREATE 1
#define BTN_DELETE 2

// Прототипы функций
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CreateRegistryKey();
void DeleteRegistryKey();


std::wstring GetTime(std::wstring btn) {
	time_t currentTime;
	struct tm localTime;
	time(&currentTime);
	localtime_s(&localTime, &currentTime);
	wchar_t timeString[256];
	wcsftime(timeString, sizeof(timeString) / sizeof(wchar_t), L"%Y-%m-%d %H:%M:%S", &localTime);
	std::wstring logMessage = L"Кнопка " + btn +  L" нажата в " + std::wstring(timeString);
	return logMessage;
}

void LogEvent(const std::wstring& message, WORD eventType) {
	HANDLE hEventLog = RegisterEventSource(NULL, L"OSISP_LAB");
	if (hEventLog != NULL) {
		const wchar_t* messageStrings[1] = { message.c_str() };
		ReportEvent(hEventLog, eventType, 0, 0, NULL, 1, 0, messageStrings, NULL);
		DeregisterEventSource(hEventLog);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                            
        CLASS_NAME,                    
        L"WinAPI Registry Example",     
        WS_OVERLAPPEDWINDOW,          
        CW_USEDEFAULT, CW_USEDEFAULT,  
        400, 200,                       
        NULL,                          
        NULL,                           
        hInstance,                     
        NULL                           
    );

    if (hwnd == NULL)
        return 0;

    CreateWindow(
        L"BUTTON",             
        L"Создать ключ",        
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  
        30, 50, 120, 30,        
        hwnd,                   
        (HMENU)BTN_CREATE,      
        hInstance,              
        NULL                    
    );

    CreateWindow(
        L"BUTTON",              
        L"Удалить ключ",       
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
        200, 50, 120, 30,       
        hwnd,                   
        (HMENU)BTN_DELETE,      
        hInstance,              
        NULL                    
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void CreateRegistryKey()
{
    HKEY hKey;
    DWORD disposition;
    LSTATUS result = RegCreateKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP_LAB", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &disposition);

    if (result == ERROR_SUCCESS)
    {
        if (disposition == REG_OPENED_EXISTING_KEY)
        {
            MessageBox(NULL, L"Ключ уже существует в реестре.", L"Уведомление", MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            const wchar_t* valueData = L"OSISP_LAB";
            RegSetValueEx(hKey, NULL, 0, REG_SZ, reinterpret_cast<const BYTE*>(valueData), (wcslen(valueData) + 1) * sizeof(wchar_t));
            MessageBox(NULL, L"Ключ успешно создан в реестре.", L"Успех", MB_OK | MB_ICONINFORMATION);
        }
        RegCloseKey(hKey);
    }
    else
    {
        MessageBox(NULL, L"Ошибка при создании ключа в реестре.", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}

void DeleteRegistryKey()
{
    if (RegDeleteKey(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP_LAB") == ERROR_SUCCESS)
    {
        MessageBox(NULL, L"Ключ успешно удален из реестра.", L"Успех", MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        MessageBox(NULL, L"Такого ключа не существует!", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) // Кнопка "Создать ключ"
        {
            CreateRegistryKey();
            LogEvent(GetTime(L"Создать ключ"), EVENTLOG_INFORMATION_TYPE);
        }
        else if (LOWORD(wParam) == 2) // Кнопка "Удалить ключ"
        {
            DeleteRegistryKey();
            LogEvent(GetTime(L"Удалить ключ"), EVENTLOG_INFORMATION_TYPE);
        }
        break;
    }
    case WM_CREATE:
    {
       
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    }
    return 0;
}