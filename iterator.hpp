#pragma once

#include "iterator.h"

namespace iterator
{
	template<typename T>
	Iterator<T>::Iterator(IIteratorProfile<T> *itProf)
	{
		this->itProf = itProf;
		index = 0;
		count = itProf->count();
	}

	template<typename T>
	Iterator<T>::~Iterator()
	{
		delete itProf;
	}

	template<typename T>
	void Iterator<T>::next(T **ppT)
	{
		itProf->get(index, ppT);
		index++;
	}

	template<typename T>
	bool Iterator<T>::hasNext()
	{
		return (index < count);
	}
}