#pragma once

namespace iterator
{
	template<class T>
	class IIteratorProfile
	{
	public:
		virtual void get(unsigned int index, T **ppT) = 0;
		virtual unsigned int count() = 0;
	};

	template<class T>
	class Iterator
	{
	private:
		IIteratorProfile<T> * itProf;
		unsigned int index;
		unsigned int count;
	public:
		Iterator(IIteratorProfile<T> *itProf);
		~Iterator();
		void next(T **ppT);
		bool hasNext();
	};
}

#include "iterator.hpp"