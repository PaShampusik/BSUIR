#include <windows.h>

HWND hButton;

// ���������� ��������� ����
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

		//�������������� ����
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_COMMAND:
	{
		// �������� ������� ���������� ����
		RECT rect;
		GetClientRect(hwnd, &rect);

		// ���������� ��������� ���������� ��� ����������� ������
		int newX = rand() % (rect.right - rect.left);  // ��������� ������ ������
		int newY = rand() % (rect.bottom - rect.top);  // ��������� ������ ������

		// ���������� ���� ������ � ����� ����������
		HWND hButton = (HWND)lParam;  // �������� ���������� ������

		// ���������, ����� ����� ���������� �� �������� �� ������� ����
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
	// ������������ ����� ����
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// ������� ����
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

	// ���������� ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// ��������� ���� ��������� ���������
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}