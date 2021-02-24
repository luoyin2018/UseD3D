#pragma once

#include "basicwin.h"

class Window
{
private:
	class WindowClass   // 单例模式
	{
	public:
		static const WCHAR* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

	private:
		WindowClass() noexcept;
		~WindowClass();

		static constexpr const WCHAR* wnd_class_name = L"Roy Direct3D Window";
		static WindowClass wnd_class_;
		HINSTANCE h_inst_;
	};

public:
	Window(int x, int y, int width, int height, const WCHAR* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

private:
	static LRESULT CALLBACK handle_msg_setup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK handle_msg_thunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT handle_msg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	
private:
	int width;
	int height;
	HWND hWnd;
};

