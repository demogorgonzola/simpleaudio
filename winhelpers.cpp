#include "stdafx.h"

#include "winhelpers.h"

BOOL winhelpers::is_main_window(HWND handle) {
	WCHAR sessionName[200] = { '\0' };
	int len = GetWindowText(handle, sessionName, 200);
	//printf("FUCKIN WHAT: %S\n", sessionName);
	return GetWindow(handle, GW_OWNER) == (HWND)0 && len > 0;// && IsWindowVisible(handle);
}

BOOL CALLBACK winhelpers::enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	DWORD process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
	{
		return TRUE;
	}

	data.best_handle = handle;
	return FALSE;
}

HWND winhelpers::find_main_window(DWORD process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.best_handle;
}