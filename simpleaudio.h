#pragma once

#ifdef SIMPLEAUDIO_EXPORTS
#define SIMPLEAUDIO_API __declspec(dllexport)
#else
#define SIMPLEAUDIO_API __declspec(dllimport)
#endif

#include "iterator.h"
//NOTE: CONVERT TO SAL NOTATION
//#include <sal.h>
#include <string>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <endpointvolume.h>

namespace simpleaudio
{
	class Interface;
	class Device;
	class Session;

	class DeviceIteratorProfile;
	class SessionIteratorProfile;

	/* Audio Devices Interface */
	class Interface
	{
	public:
		SIMPLEAUDIO_API Interface();
		SIMPLEAUDIO_API ~Interface();
		SIMPLEAUDIO_API void getDefaultDevice(Device **ppDevice);
		//SIMPLEAUDIO_API void isDefaultDevice(Device *pDevice);
		SIMPLEAUDIO_API void deviceIterator(iterator::Iterator<Device> **ppDeviceIterator);

	private:
		IMMDeviceEnumerator * pEnumerator;

		friend DeviceIteratorProfile;
	};

	/* Audio Device */
	class Device
	{
	public:
		SIMPLEAUDIO_API ~Device();
		SIMPLEAUDIO_API void setVolume(float percent);
		SIMPLEAUDIO_API float getVolume();
		SIMPLEAUDIO_API void getFriendlyName(wchar_t *friendlyName, int len);
		SIMPLEAUDIO_API void sessionIterator(iterator::Iterator<Session> **ppSessionIterator);

	private:
		Device(IMMDevice * pDevice);

		IMMDevice * pDevice;
		IAudioEndpointVolume *	pVolume;

		friend Interface;
		friend DeviceIteratorProfile;
		friend SessionIteratorProfile;
	};

	/* Audio Session */
	class Session
	{
	public:
		SIMPLEAUDIO_API ~Session();
		SIMPLEAUDIO_API void setVolume(float percent);
		SIMPLEAUDIO_API float getVolume();
		SIMPLEAUDIO_API void __thiscall getDisplayName(wchar_t *sessionName, int len);
		//SIMPLEAUDIO_API HICON getIcon();

	private:
		Session(IAudioSessionControl * pSession);

		IAudioSessionControl * pSession;
		ISimpleAudioVolume *	pVolume;

		friend SessionIteratorProfile;
	};


	/* HELPER CODE BELOW, NOT API */


	/* Iterator Profiles */
	class DeviceIteratorProfile : public iterator::IIteratorProfile<Device>
	{
	public:
		SIMPLEAUDIO_API DeviceIteratorProfile(Interface *pInterface);
		SIMPLEAUDIO_API ~DeviceIteratorProfile();
		SIMPLEAUDIO_API void get(unsigned int index, Device **ppDevice); //returns heap object
		SIMPLEAUDIO_API unsigned int count();

	private:
		IMMDeviceCollection * pDevices;
	};

	class SessionIteratorProfile : public iterator::IIteratorProfile<Session>
	{
	public:
		SIMPLEAUDIO_API SessionIteratorProfile(Device *pDevice);
		SIMPLEAUDIO_API ~SessionIteratorProfile();
		SIMPLEAUDIO_API void get(unsigned int index, Session **ppDevice); //returns heap object
		SIMPLEAUDIO_API unsigned int count();

	private:
		IAudioSessionEnumerator * pSessionEnumerator;
	};

	/* constants */
	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	const IID IID_IAudioEndpointVolume = __uuidof(IAudioEndpointVolume);
	const IID IID_IAudioSessionManager2 = __uuidof(IAudioSessionManager2);
	const IID IID_IAudioSessionControl2 = __uuidof(IAudioSessionControl2);
	const IID IID_ISimpleAudioVolume = __uuidof(ISimpleAudioVolume);
	const std::wstring UNKNOWN = L"<UNKNOWN>";
	const std::wstring SYS_SOUNDS = L"System Sounds";

	/* helper-functions */
	typedef struct {
		DWORD process_id;
		HWND best_handle;
	} handle_data;
	BOOL is_main_window(HWND handle);
	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
	HWND find_main_window(DWORD process_id);

	/* demo-function */
	SIMPLEAUDIO_API HRESULT demo();
}