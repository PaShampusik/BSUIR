#include <windows.h>

HWND hButton;

// Обработчик сообщений окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		hButton = CreateWindow(
			L"BUTTON", L"Hellow World",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0, 200, 100,
			hwnd, HMENU(1), (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
		);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		//перерисовываем окно
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_COMMAND:
	{
		// Получаем текущие координаты окна
		RECT rect;
		GetClientRect(hwnd, &rect);

		// Генерируем случайные координаты для перемещения текста
		int newX = rand() % (rect.right - rect.left);  // Учитываем размер кнопки
		int newY = rand() % (rect.bottom - rect.top);  // Учитываем размер кнопки

		// Перемещаем окно текста в новые координаты
		HWND hButton = (HWND)lParam;  // Получаем дескриптор кнопки

		// Проверяем, чтобы новые координаты не выходили за пределы окна
		if (newX < 0)
			newX = 0;
		if (newX > rect.right - rect.left - 200)
			newX = rect.right - rect.left - 200;
		if (newY < 0)
			newY = 0;
		if (newY > rect.bottom - rect.top - 100)
			newY = rect.bottom - rect.top - 100;

		SetWindowPos(hButton, NULL, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		return 0;
	}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Регистрируем класс окна
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Создаем окно
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Hello World",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);



	if (hwnd == NULL)
	{
		return 0;
	}

	// Отображаем окно
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Запускаем цикл обработки сообщений
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}