#pragma once

#include "simpleaudio.h"
#include "iterator.h"

#include <string>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <endpointvolume.h>

namespace simpleaudio_win
{
	class Interface;
	class Device;
	class Session;

	class DeviceIteratorProfile;
	class SessionIteratorProfile;

	/* Audio Devices Interface */
	class Interface : public simpleaudio::IInterface
	{
	public:
		Interface();
		~Interface();
		void getDefaultDevice(simpleaudio::IDevice **ppDevice);
		//void isDefaultDevice(simpleaudio::IDevice *pDevice);
		void deviceIterator(simpleaudio::IIterator<simpleaudio::IDevice> **ppDeviceIterator);

	private:
		IMMDeviceEnumerator * pEnumerator;

		friend DeviceIteratorProfile;
	};

	/* Audio Device */
	class Device : public simpleaudio::IDevice
	{
	public:
		~Device();
		void setVolume(float percent);
		float getVolume();
		void getName(wchar_t *friendlyName, int len);
		void sessionIterator(simpleaudio::IIterator<simpleaudio::ISession> **ppSessionIterator);

	private:
		Device(IMMDevice * pDevice);

		IMMDevice * pDevice;
		IAudioEndpointVolume *	pVolume;

		friend Interface;
		friend DeviceIteratorProfile;
		friend SessionIteratorProfile;
	};

	/* Audio Session */
	class Session : public simpleaudio::ISession
	{
	public:
		~Session();
		void setVolume(float percent);
		float getVolume();
		void getName(wchar_t *sessionName, int len);
		//HICON getIcon();

	private:
		Session(IAudioSessionControl * pSession);

		IAudioSessionControl * pSession;
		ISimpleAudioVolume *	pVolume;

		friend SessionIteratorProfile;
	};

	//

	/* Iterator Profiles */
	class DeviceIteratorProfile : public iterator::IIteratorProfile<simpleaudio::IDevice>
	{
	public:
		DeviceIteratorProfile(IMMDeviceEnumerator *pEnumerator);
		~DeviceIteratorProfile();
		void get(unsigned int index, simpleaudio::IDevice **ppDevice); //returns heap object
		unsigned int count();

	private:
		DeviceIteratorProfile(Interface *pInterface);
		IMMDeviceCollection * pDevices;
	};

	class SessionIteratorProfile : public iterator::IIteratorProfile<simpleaudio::ISession>
	{
	public:
		SessionIteratorProfile(IMMDevice * pDevice);
		~SessionIteratorProfile();
		void get(unsigned int index, simpleaudio::ISession **ppDevice); //returns heap object
		unsigned int count();

	private:
		IAudioSessionEnumerator * pSessionEnumerator;
	};
}

simpleaudio::IInterface * APIENTRY GetSimpleAudioInterface();