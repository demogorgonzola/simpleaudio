#pragma once

#include <string>
//#include <mmdeviceapi.h>
//#include <audiopolicy.h>
//#include <endpointvolume.h>

namespace winconstants
{
	//class and interface id's not needed..for now
	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	const IID IID_IAudioEndpointVolume = __uuidof(IAudioEndpointVolume);
	const IID IID_IAudioSessionManager2 = __uuidof(IAudioSessionManager2);
	const IID IID_IAudioSessionControl2 = __uuidof(IAudioSessionControl2);
	const IID IID_ISimpleAudioVolume = __uuidof(ISimpleAudioVolume);
	const std::wstring UNKNOWN = L"<UNKNOWN>";
	const std::wstring SYS_SOUNDS = L"System Sounds";
}