#pragma once

#include "simpleaudio.h"
#include "wincallbacks.h"

#include <map>
#include <string>

#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <endpointvolume.h>

using std::map;
using std::wstring;

namespace simpleaudio_win
{
	class Interface;
	class Device;
	class Session;

	/* Simple Audio Interface */
	class Interface : public simpleaudio::IInterface
	{
	public:
		Interface();
		~Interface();
		EFLAG getDefaultDevice(simpleaudio::IDevice **ppDevice);
		EFLAG isDefaultDevice(simpleaudio::IDevice *pDevice, bool *pRet);
		EFLAG deviceIterator(simpleaudio::IIterator<simpleaudio::IDevice *> **ppDeviceIterator);

	private:
		void generateWrappers();
		void destroyWrappers();
		simpleaudio::IDevice * generateWrapper(IMMDevice *pMMDevice);
		simpleaudio::IDevice * fetchDefaultDevice();

		IMMDeviceEnumerator * pEnumerator;

		map<IMMDevice *, simpleaudio::IDevice *> *pDevices;
	};

	/* Audio Device */
	class Device : public simpleaudio::IDevice
	{
	public:
		Device(IMMDevice * pDevice);
		~Device();
		EFLAG setVolume(float percent);
		EFLAG getVolume(float *pRet);
		EFLAG mute(bool *pRet);
		EFLAG isMuted(bool *pRet);
		EFLAG getName(wchar_t *name, int len);
		EFLAG sessionIterator(simpleaudio::IIterator<simpleaudio::ISession *> **ppSessionIterator);

	private:
		void generateWrappers();
		void destroyWrappers();
		simpleaudio::ISession * generateWrapper(IAudioSessionControl *pSessionControl);
		float fetchVolume();
		bool fetchMute();
		wstring *fetchName();

		IMMDevice * pDevice;
		IAudioEndpointVolume * pVolume;
		IPropertyStore *pProperties;

		map<IAudioSessionControl *, simpleaudio::ISession *> *pSessions;
	};

	/* Audio Session */
	class Session : public simpleaudio::ISession
	{
	public:
		Session(IAudioSessionControl * pSession);
		~Session();
		EFLAG setVolume(float percent);
		EFLAG getVolume(float *pRet);
		EFLAG mute(bool *pRet);
		EFLAG isMuted(bool *pRet);
		EFLAG getName(wchar_t *name, int len);

	private:
		float fetchVolume();
		bool fetchMute();
		void fetchName(wchar_t *sessionName, int len);

		IAudioSessionControl * pSession;
		ISimpleAudioVolume *	pVolume;
	};
}

simpleaudio::IInterface * APIENTRY GetSimpleAudioInterface();