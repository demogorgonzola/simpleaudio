#pragma once

#include <windows.h>
#include <fstream>

namespace winhelpers {

	void HR_CHECK(HRESULT hr);

	template <class T>
	void SAFE_RELEASE(T **ppUnk)
	{
		if (*ppUnk)
		{
			(*ppUnk)->Release();
			*ppUnk = NULL;
		}
	}

	//

	typedef struct {
		DWORD process_id;
		HWND best_handle;
	} handle_data;

	BOOL is_main_window(HWND handle);
	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
	HWND find_main_window(DWORD process_id);

	void write_text_to_log_file(const std::string &text);
}