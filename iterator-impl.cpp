#include "stdafx.h"

#include "iterator.hpp"

#ifdef SIMPLEAUDIO_EXPORTS
#define SIMPLEAUDIO_API __declspec(dllexport)
#else
#define SIMPLEAUDIO_API __declspec(dllimport)
#endif

#include "simpleaudio.h"
template class SIMPLEAUDIO_API iterator::Iterator<simpleaudio::Device>;
template class SIMPLEAUDIO_API iterator::Iterator<simpleaudio::Session>;
