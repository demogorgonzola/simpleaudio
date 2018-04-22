#pragma once

#include "iterator.h"

namespace iterator
{
	template<class T>
	Iterator<T>::Iterator(IIteratorProfile<T> *itProf)
	{
		this->itProf = itProf;
		index = 0;
		count = itProf->count();
	}

	template<class T>
	Iterator<T>::~Iterator()
	{
		delete itProf;
	}

	template<class T>
	void Iterator<T>::next(T **ppT)
	{
		itProf->get(index, ppT);
		index++;
	}

	template<class T>
	bool Iterator<T>::hasNext()
	{
		return (index < count);
	}
}