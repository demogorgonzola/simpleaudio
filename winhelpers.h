#pragma once

#include <windows.h>

namespace winhelpers {

	typedef struct {
		DWORD process_id;
		HWND best_handle;
	} handle_data;

	BOOL is_main_window(HWND handle);
	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
	HWND find_main_window(DWORD process_id);
}