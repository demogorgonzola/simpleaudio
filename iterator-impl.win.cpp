#include "stdafx.h"

#include "iterator-impl.win.h"
#include "winconstants.hpp"
#include "winhelpers.h"

#define HR_CHECK(hr) winhelpers::HR_CHECK(hr)
#define SAFE_RELEASE(pUnk) winhelpers::SAFE_RELEASE(pUnk)

/* DeviceIteratorProfile */
iteratorprofiles_win::MMDeviceIteratorProfile::MMDeviceIteratorProfile(IMMDeviceEnumerator *pEnumerator)
{
	HR_CHECK(pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices));
}

iteratorprofiles_win::MMDeviceIteratorProfile::~MMDeviceIteratorProfile()
{
	SAFE_RELEASE(&pDevices);
}

void iteratorprofiles_win::MMDeviceIteratorProfile::get(unsigned int index, IMMDevice **ppDevice)
{
	IMMDevice *pMMDevice;
	HR_CHECK(pDevices->Item(index, &pMMDevice));
	*ppDevice = pMMDevice;
}

unsigned int iteratorprofiles_win::MMDeviceIteratorProfile::count()
{
	unsigned int count;
	HR_CHECK(pDevices->GetCount(&count));
	return count;
}

/* SessionIteratorProfile */
iteratorprofiles_win::AudioSessionControlIteratorProfile::AudioSessionControlIteratorProfile(IMMDevice *pDevice)
{
	IAudioSessionManager2 *pSessionManager;
	HR_CHECK(pDevice->Activate(winconstants::IID_IAudioSessionManager2, CLSCTX_ALL, NULL, (void **)&pSessionManager));
	HR_CHECK(pSessionManager->GetSessionEnumerator(&pSessionEnumerator));
	SAFE_RELEASE(&pSessionManager);
}

iteratorprofiles_win::AudioSessionControlIteratorProfile::~AudioSessionControlIteratorProfile()
{
	SAFE_RELEASE(&pSessionEnumerator);
}

void iteratorprofiles_win::AudioSessionControlIteratorProfile::get(unsigned int index, IAudioSessionControl **ppSession)
{
	IAudioSessionControl *pSessionControl;
	HR_CHECK(pSessionEnumerator->GetSession((int)index, &pSessionControl));
	*ppSession = pSessionControl;
}

unsigned int iteratorprofiles_win::AudioSessionControlIteratorProfile::count()
{
	int count;
	HR_CHECK(pSessionEnumerator->GetCount(&count));
	return static_cast<unsigned int>(count);
}