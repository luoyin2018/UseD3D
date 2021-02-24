#include <windows.h>
#include "Window.h"


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	Window wnd(100, 100, 800, 300, L"Hello, windows!");
	Window wnd2(100, 100, 300, 800, L"Hello, windows!");

	MSG msg;
	BOOL g_Result;

	while((g_Result = GetMessage(&msg, nullptr, 0, 0))>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return g_Result == -1 ? -1 : int(msg.wParam);
}