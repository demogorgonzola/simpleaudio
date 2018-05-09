#pragma once

#include "iterator.h"

#include <iostream>

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
	void Iterator<T>::next(T *pT)
	{
		itProf->get(index, pT);
		index++;
	}

	template<typename T>
	bool Iterator<T>::hasNext()
	{
		return (index < count);
	}

	/* MapValue Iterator Profile */
	template<typename T, typename U>
	MapValueIteratorProfile<T, U>::MapValueIteratorProfile(std::map<T, U> *pUs)
	{
		this->pUs = new vector<U>();
		typename map<T, U>::iterator it;
		for (it = pUs->begin(); it != pUs->end(); ++it)
		{
			this->pUs->push_back(it->second);
		}
	}

	template<typename T, typename U>
	MapValueIteratorProfile<T, U>::~MapValueIteratorProfile()
	{
		delete pUs;
	}

	template<typename T, typename U>
	void MapValueIteratorProfile<T, U>::get(unsigned int index, U *pU)
	{
		*pU = pUs->at(index);
	}

	template<typename T, typename U>
	unsigned int MapValueIteratorProfile<T, U>::count()
	{
		return pUs->size();
	}
}