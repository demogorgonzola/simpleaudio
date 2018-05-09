#pragma once

#include <string>
//#include <mmdeviceapi.h>
//#include <audiopolicy.h>
//#include <endpointvolume.h>

namespace winconstants
{
	// {EF953D1F-6059-4BA4-A73C-49096016F577}
	static const GUID program_id = { 0xef953d1f, 0x6059, 0x4ba4,{ 0xa7, 0x3c, 0x49, 0x9, 0x60, 0x16, 0xf5, 0x77 } };
	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	const IID IID_IAudioEndpointVolume = __uuidof(IAudioEndpointVolume);
	const IID IID_IAudioSessionManager2 = __uuidof(IAudioSessionManager2);
	const IID IID_IAudioSessionControl2 = __uuidof(IAudioSessionControl2);
	const IID IID_ISimpleAudioVolume = __uuidof(ISimpleAudioVolume);
	const std::wstring UNKNOWN = L"<UNKNOWN>";
	const std::wstring SYS_SOUNDS = L"System Sounds";
}