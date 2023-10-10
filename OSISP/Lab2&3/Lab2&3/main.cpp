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
#include <chrono>
#include <thread>

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

//
//   FUNCTION: CaptureAnImage(HWND hWnd)
//
//   PURPOSE: Captures a screenshot into a window ,and then saves it in a .bmp file.
//
//   COMMENTS: 
//
//      Note: This function attempts to create a file called captureqwsx.bmp 
//        

int CaptureAnImage(HWND hWnd)
{
	HDC hdcScreen;
	HDC hdcWindow;
	HDC hdcMemDC = NULL;
	HBITMAP hbmScreen = NULL;
	BITMAP bmpScreen;
	DWORD dwBytesWritten = 0;
	DWORD dwSizeofDIB = 0;
	HANDLE hFile = NULL;
	char* lpbitmap = NULL;
	HANDLE hDIB = NULL;
	DWORD dwBmpSize = 0;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL);
	hdcWindow = GetDC(hWnd);

	// Create a compatible DC, which is used in a BitBlt from the window DC.
	hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!hdcMemDC)
	{
		MessageBox(hWnd, L"CreateCompatibleDC has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the client area for size calculation.
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	// This is the best stretch mode.
	SetStretchBltMode(hdcWindow, HALFTONE);

	// The source DC is the entire screen, and the destination DC is the current window (HWND).
	if (!StretchBlt(hdcWindow,
		0, 0,
		rcClient.right, rcClient.bottom,
		hdcScreen,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY))
	{
		MessageBox(hWnd, L"StretchBlt has failed", L"Failed", MB_OK);
		goto done;
	}

	// Create a compatible bitmap from the Window DC.
	hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

	if (!hbmScreen)
	{
		MessageBox(hWnd, L"CreateCompatibleBitmap Failed", L"Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(hdcMemDC,
		0, 0,
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		hdcWindow,
		0, 0,
		SRCCOPY))
	{
		MessageBox(hWnd, L"BitBlt has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the BITMAP from the HBITMAP.
	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	hDIB = GlobalAlloc(GHND, dwBmpSize);
	lpbitmap = (char*)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap, and copies them into a buffer 
	// that's pointed to by lpbitmap.
	GetDIBits(hdcWindow, hbmScreen, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap,
		(BITMAPINFO*)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	hFile = CreateFile(L"captureqwsx.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size.
	dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	// Size of the file.
	bmfHeader.bfSize = dwSizeofDIB;

	// bfType must always be BM for Bitmaps.
	bmfHeader.bfType = 0x4D42; // BM.

	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	// Unlock and Free the DIB from the heap.
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	// Close the handle for the file that was created.
	CloseHandle(hFile);

	// Clean up.
done:
	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

	return 0;
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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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
		using namespace std::this_thread; // sleep_for, sleep_until
		using namespace std::chrono; // nanoseconds, system_clock, seconds
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
		CaptureAnImage(hWnd);
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