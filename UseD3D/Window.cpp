#include "Window.h"

Window::WindowClass Window::WindowClass::wnd_class_;

Window::WindowClass::WindowClass() noexcept
	:h_inst_(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = {
	.cbSize = sizeof(wc),
	.style = CS_OWNDC,
	.lpfnWndProc = handle_msg_setup,
	.cbClsExtra = 0,
	.cbWndExtra = 0,
	.hInstance = GetInstance(),
	.hIcon = nullptr,
	.hCursor = nullptr,
	.hbrBackground = nullptr,
	.lpszMenuName = nullptr,
	.lpszClassName = GetName(),
	.hIconSm = nullptr };

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wnd_class_name, GetInstance());
}


const WCHAR* Window::WindowClass::GetName() noexcept
{
	return wnd_class_name;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wnd_class_.h_inst_;
}

Window::Window(int x, int y, int width, int height, const WCHAR* name)
	:width(width), height(height)
{
	RECT wr;
	wr.left = x;
	wr.right = x + width;
	wr.top = y;
	wr.bottom = y + height;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZE | WS_SYSMENU, false); // 将边框考虑进来

	hWnd = CreateWindow(
		WindowClass::GetName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	//if(hWnd==nullptr)

	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::handle_msg_setup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if(msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		const auto pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handle_msg_thunk));

		return pWnd->handle_msg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::handle_msg_thunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	const auto pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->handle_msg(hWnd, msg, wParam, lParam);
}

LRESULT Window::handle_msg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		return 0;    // 由Window的析构函数来销毁窗口，不使用DefWndProc
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_CHAR:
		break;
	case WM_LBUTTONDOWN:
	{
		const auto pt = MAKEPOINTS(lParam);

	}
	break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
