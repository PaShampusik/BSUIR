#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shobjidl_core.h>
#include <vector>
#include <codecvt>
#include <thread>
#include <math.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

struct CountryData
{
	std::string name;
	float value;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::vector<CountryData> countryDataList;

void getData(HWND hWnd);

void onPaint(HWND hWnd);  

void playAudio();

HHOOK hKeyboardHook;

// Keyboard hook procedure
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN) {
			KBDLLHOOKSTRUCT* pKeyboardHookStruct = (KBDLLHOOKSTRUCT*)lParam;
			if (pKeyboardHookStruct->vkCode == VK_SPACE)
			{
				// Ctrl key is pressed
				playAudio();
			}
		}
	}

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void playAudio() {
	PlaySound(L"audio.wav", NULL, SND_FILENAME);
	return;
} 

void SetHook()
{
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
}

void RemoveHook()  
{
	UnhookWindowsHookEx(hKeyboardHook);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	SetHook();
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,// window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	RemoveHook();
	return msg.wParam;
}  // WinMain

std::string OpenFile(HWND hwnd) {
	IFileOpenDialog* pFileOpen;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
		IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

	if (SUCCEEDED(hr)) {
		hr = pFileOpen->Show(NULL);

		if (SUCCEEDED(hr)) {
			IShellItem* pItem;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr)) {
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				if (SUCCEEDED(hr)) {
					std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
					std::string filePath = converter.to_bytes(pszFilePath);
					CoTaskMemFree(pszFilePath); // Free the allocated memory
					return filePath;
				}
			}
		}
		pFileOpen->Release();
	}
	return "";
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_CREATE:
		
		getData(hWnd);
		return 0;

	case WM_PAINT:

		onPaint(hWnd);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void getData(HWND hWnd) {
	std::ifstream inputFile;
	std::string file;
	std::string name;

	file = OpenFile(hWnd);
	inputFile.open(file, std::ifstream::out);
	if (!inputFile)
	{
		std::cout << "Не удалось открыть файл." << std::endl;
		return;
	}

	// Чтение данных из файла
	float value;
	while (inputFile >> name >> value)
	{
		countryDataList.push_back({ name, value });
	}

	// Закрытие файла после чтения
	inputFile.close();
}

void onPaint(HWND hWnd) {

	HDC hdc;
	std::wstring temp;
	RECT rect;
	PAINTSTRUCT  ps;
	int nX = 400;
	int nY = 200;
	int tx = 300;
	int ty = 420;
	DWORD dwRadius = 150;
	float sum = 0;
	float step = 0;
	int brushStep = 0;
	int brushColor = 0;
	float angle = 0;

	for (const auto country : countryDataList) {
		sum += country.value;
	}
	brushStep = 255 / countryDataList.size();
	brushColor = brushStep;

	hdc = BeginPaint(hWnd, &ps);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCBrushColor(hdc, RGB(brushColor, brushColor, brushColor));

	for (int i = 0; i < countryDataList.size(); i++) {
		step += countryDataList[i].value / sum * 360;
		BeginPath(hdc);
		MoveToEx(hdc, nX, nY, (LPPOINT)NULL);
		AngleArc(hdc, nX, nY, dwRadius, angle, step - angle);
		MoveToEx(hdc, nX, nY, (LPPOINT)NULL);
		angle = step;
		LineTo(hdc, nX, nY);
		SetDCBrushColor(hdc, RGB(abs((brushColor * 7 - 30) % 255), 255 - brushColor ,  abs((255 - brushColor * 3) % 255)));
		SetTextColor(hdc, RGB(abs((brushColor * 7 - 30) % 255), 255 - brushColor, abs((255 - brushColor * 3) % 255)));

		rect.left = tx;
		rect.right = tx + 40;
		rect.top = ty;
		rect.bottom = ty + 30;

		temp = std::wstring(countryDataList[i].name.begin(), countryDataList[i].name.end());

		tx += 80;

		brushColor += brushStep;

		EndPath(hdc);
		StrokeAndFillPath(hdc);

		DrawTextW(hdc, temp.c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP);
	}
	StrokeAndFillPath(hdc);
	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}