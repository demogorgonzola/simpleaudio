#pragma once

#include "simpleaudio.h"

#include <map>
#include <vector>

using std::map;
using std::vector;

namespace iterator
{
	template<typename T>
	class IIteratorProfile
	{
	public:
		virtual void get(unsigned int index, T *pT) = 0;
		virtual unsigned int count() = 0;
	};

	template<typename T>
	class Iterator : public simpleaudio::IIterator<T>
	{
	private:
		IIteratorProfile<T> * itProf;
		unsigned int index;
		unsigned int count;
	public:
		Iterator(IIteratorProfile<T> *itProf);
		~Iterator();
		void next(T *pT);
		bool hasNext();
	};

	template<typename T, typename U>
	class MapValueIteratorProfile : public iterator::IIteratorProfile<U>
	{
	public:
		MapValueIteratorProfile(map<T, U> *pUs);
		~MapValueIteratorProfile();
		void get(unsigned int index, U *pU);
		unsigned int count();

	private:
		vector<U> *pUs;
	};
}

#include "iterator.hpp"