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

constexpr int NUM_THREADS = 4;
constexpr int NUM_ITERATIONS = 200000000;


struct CountryData
{
	std::string name;
	float value;
};

// Функция, выполняемая в потоке
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	auto start = std::chrono::high_resolution_clock::now();

	// Выполнение сложной математической задачи
	for (int i = 0; i < NUM_ITERATIONS; ++i)
	{
		double result = sqrt(sqrt(i * i));
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	return static_cast<DWORD>(duration);
}

void RunThreadsWithDifferentPriorities()
{
	HANDLE threads[NUM_THREADS];
	DWORD threadIds[NUM_THREADS];
	int priorities[NUM_THREADS] = { THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_BELOW_NORMAL,
								   THREAD_PRIORITY_NORMAL, THREAD_PRIORITY_TIME_CRITICAL };

	std::cout << "Запуск потоков с разными приоритетами..." << std::endl;

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		threads[i] = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &threadIds[i]);
		if (threads[i] != NULL)
		{
			SetThreadPriority(threads[i], priorities[i]);
		}
	}

	std::cout << "Ожидание завершения потоков..." << std::endl;

	DWORD durations[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		WaitForSingleObject(threads[i], INFINITE);
		GetExitCodeThread(threads[i], &durations[i]);
		CloseHandle(threads[i]);
	}

	std::cout << "Результаты:" << std::endl;
	std::ofstream outputFile("results.txt");
	if (outputFile.is_open())
	{
		for (int i = 0; i < NUM_THREADS; ++i)
		{
			outputFile << "Thread" << i + 1 <<  " " << durations[i] << " ";
		}
		outputFile.close();
		std::cout << "Результаты записаны в файл 'results.txt'" << std::endl;
	}
	else
	{
		std::cerr << "Ошибка при открытии файла для записи результатов." << std::endl;
	}
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::vector<CountryData> countryDataList;

void getData(HWND hWnd);

void onPaint(HWND hWnd);

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

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
		0,            // initial x position
		0,            // initial y position
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
	return msg.wParam;
}  // WinMain


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		RunThreadsWithDifferentPriorities();
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
	std::string file = "results.txt";
	std::string name;

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
		SetDCBrushColor(hdc, RGB(abs((brushColor * 7 - 30) % 255), 255 - brushColor, abs((255 - brushColor * 3) % 255)));
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