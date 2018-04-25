#include "stdafx.h"

#include "simpleaudio.win.h"
#include "winconstants.hpp"
#include "winhelpers.h"

#include <functiondiscoverykeys_devpkey.h>

#include <iostream>

using std::cout;
using std::wcout;
using std::endl;

void HR_CHECK(HRESULT hr)
{
	if (hr != S_OK)
	{
		cout << "NOOOOOOOOOOO" << endl;
		throw "BAD HRESULT";
	}
}

template <class T> void SAFE_RELEASE(T **ppUnk)
{
	if (*ppUnk)
	{
		(*ppUnk)->Release();
		*ppUnk = NULL;
	}
}

#define HR_CHECK(hr) HR_CHECK(hr)
#define SAFE_RELEASE(pUnk) SAFE_RELEASE(pUnk)

/* Device Interface */
simpleaudio_win::Interface::Interface()
{
	//Note: To use Compoment Objects (Co's) you have to initialize the COM library on the current thread before they can be used."
	CoInitialize(NULL);
	HR_CHECK(CoCreateInstance(winconstants::CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, winconstants::IID_IMMDeviceEnumerator, (void **)&pEnumerator));
}

simpleaudio_win::Interface::~Interface()
{
	SAFE_RELEASE(&pEnumerator);
	CoUninitialize();
}

void simpleaudio_win::Interface::getDefaultDevice(simpleaudio::IDevice **ppDevice)
{
	IMMDevice *pMMDevice;
	HR_CHECK(pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pMMDevice));
	*ppDevice = new Device(pMMDevice);
}

void simpleaudio_win::Interface::deviceIterator(simpleaudio::IIterator<simpleaudio::IDevice> **ppDeviceIterator)
{
	DeviceIteratorProfile *itProf = new DeviceIteratorProfile(pEnumerator);
	*ppDeviceIterator = new iterator::Iterator<simpleaudio::IDevice>(itProf);
	simpleaudio::IIterator<simpleaudio::IDevice> *as = new iterator::Iterator<simpleaudio::IDevice>(itProf);
}

/* Device */
simpleaudio_win::Device::Device(IMMDevice * pDevice)
{
	pDevice->AddRef();
	this->pDevice = pDevice;
	HR_CHECK(pDevice->Activate(winconstants::IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (void **)&pVolume));
}

simpleaudio_win::Device::~Device()
{
	SAFE_RELEASE(&pDevice);
	SAFE_RELEASE(&pVolume);
}

void simpleaudio_win::Device::setVolume(float percent)
{
	HR_CHECK(pVolume->SetMasterVolumeLevelScalar(percent, NULL));
}

float simpleaudio_win::Device::getVolume()
{
	float percent;
	HR_CHECK(pVolume->GetMasterVolumeLevelScalar(&percent));
	return percent;
}

void simpleaudio_win::Device::getName(wchar_t *friendlyName, int len)
{
	IPropertyStore *pProperties;
	PROPVARIANT prop;
	PropVariantInit(&prop);

	HR_CHECK(pDevice->OpenPropertyStore(STGM_READ, &pProperties));
	HR_CHECK(pProperties->GetValue(PKEY_Device_FriendlyName, &prop));
	wcscpy_s(friendlyName, len, prop.pwszVal);

	PropVariantClear(&prop);
	SAFE_RELEASE(&pProperties);
}

void simpleaudio_win::Device::sessionIterator(simpleaudio::IIterator<simpleaudio::ISession> **ppSessionIterator)
{
	SessionIteratorProfile *itProf = new SessionIteratorProfile(pDevice);
	*ppSessionIterator = new iterator::Iterator<simpleaudio::ISession>(itProf);
}

/* Session */
simpleaudio_win::Session::Session(IAudioSessionControl * pSession)
{
	pSession->AddRef();
	this->pSession = pSession;
	//Note: This isn't documented in the MSDN use of QueryInterface, but has multiple recent reports of reliable use *EYES-UP* do research and understand why this happens
	HR_CHECK(this->pSession->QueryInterface(winconstants::IID_ISimpleAudioVolume, (void **)&pVolume));
}

simpleaudio_win::Session::~Session()
{
	SAFE_RELEASE(&this->pSession);
	SAFE_RELEASE(&this->pVolume);
}

void simpleaudio_win::Session::setVolume(float percent)
{
	HR_CHECK(pVolume->SetMasterVolume(percent, NULL));
}

float simpleaudio_win::Session::getVolume()
{
	float volume;
	HR_CHECK(pVolume->GetMasterVolume(&volume));
	return volume;
}

void simpleaudio_win::Session::getName(wchar_t *sessionName, int len)
{
	IAudioSessionControl2 *pSessionControl2;
	DWORD processId;
	HWND handle;
	HR_CHECK(pSession->QueryInterface(winconstants::IID_IAudioSessionControl2, (void **)&pSessionControl2));
	if (pSessionControl2->IsSystemSoundsSession())
	{
		HR_CHECK(pSessionControl2->GetProcessId(&processId));
		handle = winhelpers::find_main_window(processId);
		*sessionName = L'\0';
		GetWindowText(handle, sessionName, len);
		if (*sessionName == L'\0')
		{
			wcscpy_s(sessionName, len, winconstants::UNKNOWN.c_str());
		}
	}
	else
	{
		wcscpy_s(sessionName, len, winconstants::SYS_SOUNDS.c_str());
	}

	SAFE_RELEASE(&pSessionControl2);
}

/* DeviceIteratorProfile */
simpleaudio_win::DeviceIteratorProfile::DeviceIteratorProfile(IMMDeviceEnumerator *pEnumerator)
{
	HR_CHECK(pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices));
}

simpleaudio_win::DeviceIteratorProfile::~DeviceIteratorProfile()
{
	SAFE_RELEASE(&pDevices);
}

void simpleaudio_win::DeviceIteratorProfile::get(unsigned int index, simpleaudio::IDevice **ppDevice)
{
	IMMDevice *pMMDevice;
	HR_CHECK(pDevices->Item(index, &pMMDevice));
	*ppDevice = new Device(pMMDevice);
	SAFE_RELEASE(&pMMDevice);
}

unsigned int simpleaudio_win::DeviceIteratorProfile::count()
{
	unsigned int count;
	HR_CHECK(pDevices->GetCount(&count));
	return count;
}

/* SessionIteratorProfile */
simpleaudio_win::SessionIteratorProfile::SessionIteratorProfile(IMMDevice *pDevice)
{
	IAudioSessionManager2 *pSessionManager;
	HR_CHECK(pDevice->Activate(winconstants::IID_IAudioSessionManager2, CLSCTX_ALL, NULL, (void **)&pSessionManager));
	HR_CHECK(pSessionManager->GetSessionEnumerator(&pSessionEnumerator));
	SAFE_RELEASE(&pSessionManager);
}

simpleaudio_win::SessionIteratorProfile::~SessionIteratorProfile()
{
	SAFE_RELEASE(&pSessionEnumerator);
}

void simpleaudio_win::SessionIteratorProfile::get(unsigned int index, simpleaudio::ISession **ppSession)
{
	IAudioSessionControl *pSessionControl;
	HR_CHECK(pSessionEnumerator->GetSession((int)index, &pSessionControl));
	*ppSession = new Session(pSessionControl);
	SAFE_RELEASE(&pSessionControl);
}

unsigned int simpleaudio_win::SessionIteratorProfile::count()
{
	int count;
	HR_CHECK(pSessionEnumerator->GetCount(&count));
	return static_cast<unsigned int>(count);
}

simpleaudio::IInterface * APIENTRY GetSimpleAudioInterface()
{
	return new simpleaudio_win::Interface();
}