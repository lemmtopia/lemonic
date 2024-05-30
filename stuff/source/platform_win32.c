#include "platform.h"

#ifdef LEM_PLATFORM_WIN32

#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
    HINSTANCE instance_handle;
    HWND window_handle;
} internal_state;

static f64 clock_freq;
static LARGE_INTEGER start_time;

static b8 should_exit;

LRESULT CALLBACK win32_window_proc(HWND window, u32 message, WPARAM wparam, LPARAM lparam);

b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 width,
    i32 height)
{
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)plat_state->internal_state;

    state->instance_handle = GetModuleHandleA(0);

    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = state->instance_handle;
    wc.lpfnWndProc = win32_window_proc;
    wc.hIcon = LoadIcon(state->instance_handle, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "lemonic_window_class";

    if (!RegisterClassA(&wc))
    {
	MessageBoxA(0, "window registration failed", "lemonic error", MB_OK | MB_ICONEXCLAMATION);
	return FALSE;
    }

    u32 client_x = CW_USEDEFAULT;
    u32 client_y = CW_USEDEFAULT;
    u32 client_width = width;
    u32 client_height = height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
    u32 window_ex_style = WS_EX_APPWINDOW;
    RECT border = {0, 0, 0, 0};
    AdjustWindowRectEx(&border, window_style, 0, window_ex_style);

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width + (border.right - border.left);
    u32 window_height = client_height + (border.bottom - border.top);
    
    HWND handle = CreateWindowExA(
	window_ex_style,
	wc.lpszClassName,
	application_name,
	window_style,
	window_x, window_y,
	window_width, window_height,
	0, 0, state->instance_handle, 0);

    if (handle == 0)
    {
	MessageBoxA(NULL, "window creation failed", "lemonic error",
		    MB_OK | MB_ICONEXCLAMATION);
	return FALSE;
    }
    else
    {
	state->window_handle = handle;
    }


    b32 should_activate = 1;
    i32 show_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ShowWindow(state->window_handle, show_flags);
    
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    clock_freq = 1.0 / (f64)freq.QuadPart;
    QueryPerformanceCounter(&start_time);

    should_exit = FALSE;
    return TRUE;
}

void platform_shutdown(platform_state* plat_state)
{
    internal_state* state = (internal_state*)plat_state->internal_state;

    if (state->window_handle)
    {
	DestroyWindow(state->window_handle);
	state->window_handle = 0;
    }
}

b8 platform_pump_messages(platform_state* plat_state)
{
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
    {
	TranslateMessage(&message);
	DispatchMessageA(&message);
    }

    if (should_exit) return FALSE;
    
    return TRUE;
}

void* platform_alloc(u64 size, b8 aligned)
{
    // TODO: Change this
    return malloc(size);
}
void platform_free(void* block, u64 size)
{
    free(block);
}

void* platform_memset(void* block, i32 value, u64 size)
{
    return memset(block, value, size);
}

f64 platform_get_abs_time()
{
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);

    return (f64)current_time.QuadPart * clock_freq;
}

void platform_sleep(u64 ms)
{
    Sleep(ms);
}

void platform_console_write(const char* message)
{
    u64 length = strlen(message);
    LPDWORD num_written = 0;
    
    WriteConsoleA(
	GetStdHandle(STD_OUTPUT_HANDLE),
	message,
	(DWORD)length,
	num_written, 0);
}

LRESULT CALLBACK win32_window_proc(HWND window, u32 message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_CLOSE:
	// TODO: fire an event for quitting the application
	should_exit = TRUE;
	return 0;
    case WM_DESTROY:
	should_exit = TRUE;
	PostQuitMessage(0);
	return 0; // break is not necessary when we use return cuz we exit
    case WM_SIZE:
    {
	// TODO: fire and event for window resizing.
    } break;
    }

    return DefWindowProc(window, message, wparam, lparam);
}

#endif
