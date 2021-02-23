#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_CHAR:
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	const auto pClassName = L"hw3d_study";
	WNDCLASSEX wc = {
		.cbSize = sizeof(wc),
		.style = CS_OWNDC,
		.lpfnWndProc = WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hInstance,
		.hIcon = nullptr,
		.hCursor = nullptr,
		.hbrBackground = nullptr,
		.lpszMenuName = nullptr,
		.lpszClassName = pClassName,
		.hIconSm = nullptr };

	RegisterClassEx(&wc);

	const auto h_wnd = CreateWindowEx(
		0, pClassName,
		L"HELLO DirectX",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(h_wnd, SW_SHOW);

	MSG msg;
	BOOL g_Result;

	while((g_Result = GetMessage(&msg, nullptr, 0, 0))>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return g_Result == -1 ? -1 : int(msg.wParam);
}