# simpleaudio

A simple volume mixer library for Windows.

This library directly wraps COM Interfaces of MMDevice API, WASAPI, and EndPointVolume API and provides a more user-friendly way to control:
* Volume of a Device (Scalar)   e.g. Speakers 0%-100%
* Volume of a Session (Scalar)  e.g. Chrome 0%-100%
* (insert later features here)

To see direct implementation of the Audio Libraries COM Interfaces visit: simpleaudio.win.h, simpleaudio.win.cpp
