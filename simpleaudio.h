#pragma once

#ifdef SIMPLEAUDIO_EXPORTS
#define SIMPLEAUDIO_API __declspec(dllexport)
#else
#define SIMPLEAUDIO_API __declspec(dllimport)
#endif

#ifdef _WIN32
#include <Windows.h>
#else
#define APIENTRY
#endif

namespace simpleaudio 
{
	class IInterface;
	class IAudioEntity;
	class IDevice;
	class ISession;

	template<typename T>
	class IIterator
	{
	public:
		virtual void next(T **ppT) = 0;
		virtual bool hasNext() = 0;
	};

	/* Simple Audio Interface */
	class IInterface
	{
	public:
		virtual void getDefaultDevice(IDevice **ppDevice) = 0;
		//virtual void isDefaultDevice(IDevice *pDevice) = 0;
		virtual void deviceIterator(IIterator<IDevice> **ppDeviceIterator) = 0;
	};

	/* Audio Entity */
	class IAudioEntity
	{
	public:
		virtual void setVolume(float percent) = 0;
		virtual float getVolume() = 0;
		virtual void getName(wchar_t *friendlyName, int len) = 0;
	};

	/* Audio Device */
	class IDevice : public virtual IAudioEntity
	{
	public:
		virtual void sessionIterator(IIterator<ISession> **ppSessionIterator) = 0;
	};

	/* Audio Session */
	class ISession : public virtual IAudioEntity
	{
	public:
		//virtual HICON getIcon() = 0;
	};
}

extern "C" SIMPLEAUDIO_API simpleaudio::IInterface * APIENTRY GetSimpleAudioInterface();