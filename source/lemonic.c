#include "lemonic.h"

#include <windows.h>
#include <string.h>

typedef struct
{
    HINSTANCE instance;
    HWND window;
} platform_state;

static platform_state plat_state;
b8 is_running = FALSE;

LRESULT CALLBACK WndProc(HWND window, u32 message, WPARAM wparam, LPARAM lparam);

void lemonic_open_window(const char* title, i32 width, i32 height)
{
    plat_state.instance = GetModuleHandleA(0);

    WNDCLASSA wc;
    memset(&wc, 0, sizeof(WNDCLASSA));

    wc.lpszClassName = "lemonic_window_class";
    wc.lpfnWndProc = WndProc;
    wc.hInstance = plat_state.instance;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // TODO: logging
    RegisterClassA(&wc);

    // TODO: logging
    plat_state.window = CreateWindowA(
	wc.lpszClassName,
	title,
	WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	width, height,
	0, 0, plat_state.instance, 0);

    i32 show_flags = SW_SHOW;
    ShowWindow(plat_state.window, show_flags);
    
    is_running = TRUE;
}

b8 lemonic_is_running()
{
    return is_running;
}

void lemonic_message_loop()
{
    MSG message;
    if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
	TranslateMessage(&message);
	DispatchMessageA(&message);
    }
}

LRESULT CALLBACK WndProc(HWND window, u32 message, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;

    switch (message)
    {
    case WM_QUIT:
    case WM_DESTROY:
	is_running = FALSE;
	break;
    default:
	result = DefWindowProc(window, message, wparam, lparam);
	break;
    }
    
    return result;
}
