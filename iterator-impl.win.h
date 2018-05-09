#pragma once

#include "iterator.h"
#include "simpleaudio.win.h"

namespace iteratorprofiles_win {
	/* Device Iterator Profile */
	class MMDeviceIteratorProfile : public iterator::IIteratorProfile<IMMDevice *>
	{
	public:
		MMDeviceIteratorProfile(IMMDeviceEnumerator *pEnumerator);
		~MMDeviceIteratorProfile();
		void get(unsigned int index, IMMDevice **ppDevice);
		unsigned int count();

	private:
		IMMDeviceCollection * pDevices;
	};

	/* Session Iterator Profile */
	class AudioSessionControlIteratorProfile : public iterator::IIteratorProfile<IAudioSessionControl *>
	{
	public:
		AudioSessionControlIteratorProfile(IMMDevice *pDevice);
		~AudioSessionControlIteratorProfile();
		void get(unsigned int index, IAudioSessionControl **pSession);
		unsigned int count();

	private:
		IAudioSessionEnumerator * pSessionEnumerator;
	};
}