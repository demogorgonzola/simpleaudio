#include "stdafx.h"

#include "winhelpers.h"

#include <string>


void winhelpers::HR_CHECK(HRESULT hr)
{
	if (hr != S_OK)
	{
		throw hr;
	}
}

BOOL winhelpers::is_main_window(HWND handle) {
	WCHAR sessionName[200] = { '\0' };
	int len = GetWindowText(handle, sessionName, 200);
	return GetWindow(handle, GW_OWNER) == (HWND)0 && len > 0;
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

void winhelpers::write_text_to_log_file(const std::string &text)
{
	std::ofstream log_file(
		"log_file.txt", std::ios_base::out | std::ios_base::app);
	log_file << text << std::endl;
}



void guid_to_wstr(GUID guid, wchar_t**wstr)
{
	int guid_str_len = 38;
	wchar_t *temp = new wchar_t[guid_str_len];
	swprintf(temp, guid_str_len, \
		L"{%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}", \
		guid.Data1, guid.Data2, guid.Data3, \
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], \
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
	);
	*wstr = temp;
}