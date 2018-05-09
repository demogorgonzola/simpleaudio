#pragma once

#ifdef SIMPLEAUDIO_EXPORTS
#define SIMPLEAUDIO_API __declspec(dllexport)
#else
#define SIMPLEAUDIO_API __declspec(dllimport)
#endif

#ifdef _WIN32
#include <Windows.h>
typedef HRESULT EFLAG;
#else
#define APIENTRY
typedef int EFLAG;
#endif

namespace simpleaudio 
{
	class IInterface;
	class IAudioEntity;
	class IDevice;
	class ISession;

	class IInterfaceCallback;
	class IDeviceCallback;
	class ISessionCallback;

	/* Iterator */
	template<typename T>
	class IIterator
	{
	public:
		virtual void next(T *pT) = 0;
		virtual bool hasNext() = 0;
	};

	/* Simple Audio Interface */
	class IInterface
	{
	public:
		virtual EFLAG getDefaultDevice(IDevice **ppDevice) = 0;
		virtual EFLAG isDefaultDevice(IDevice *pDevice, bool *pRet) = 0;
		virtual EFLAG deviceIterator(IIterator<IDevice *> **ppDeviceIterator) = 0;
		//virtual EFLAG registerCallback(IInterfaceCallback *pInterfaceCallback) = 0;
	};

	/* Audio Entity */
	class IAudioEntity
	{
	public:
		virtual EFLAG setVolume(float percent) = 0;
		virtual EFLAG getVolume(float *pRet) = 0;
		virtual EFLAG mute(bool *pRet) = 0;
		virtual EFLAG isMuted(bool *pRet) = 0;
		virtual EFLAG getName(wchar_t *name, int len) = 0;
	};

	/* Audio Device */
	class IDevice : public virtual IAudioEntity
	{
	public:
		virtual EFLAG sessionIterator(IIterator<ISession *> **ppSessionIterator) = 0;
		//virtual EFLAG registerCallback(IDeviceCallback *pDeviceCallback) = 0;
	};

	/* Audio Session */
	class ISession : public virtual IAudioEntity
	{
	public:
		//virtual EFLAG registerCallback(ISessionCallback *pSessionCallback) = 0;
	};

	// callbacks

	/* Inteface Callback */
	class IInterfaceCallback
	{
	public:
		virtual EFLAG OnDefaultDeviceChanged(IDevice *pDevice) = 0;
		virtual EFLAG OnDeviceAdded(IDevice *pDevice) = 0;
		virtual EFLAG OnDeviceRemoved(IDevice *pDevice) = 0;
	};

	/* Device Callback */
	class IDeviceCallback
	{
	public:
		virtual EFLAG OnVolumeChanged(float newVolume) = 0;
		virtual EFLAG OnMute(bool toggleState) = 0;
		virtual EFLAG OnNameChanged(wchar_t *newName) = 0;
		virtual EFLAG OnSessionCreated(ISession *pSession) = 0;
		virtual EFLAG OnSessionDisconnected(ISession *pSession) = 0;
	};

	/* Session Callback */
	class ISessionCallback
	{
	public:
		virtual EFLAG OnVolumeChanged(float newVolume) = 0;
		virtual EFLAG OnMute(bool toggleState) = 0;
		virtual EFLAG OnNameChanged(wchar_t *newName) = 0;
	};
}

extern "C" SIMPLEAUDIO_API simpleaudio::IInterface * APIENTRY GetSimpleAudioInterface();