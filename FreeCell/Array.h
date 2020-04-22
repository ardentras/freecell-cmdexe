/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Array.h
* Date Created:		01/10/2017
* Modifications:	
					01/20/2017 - Documentation.
************************************************************/

#pragma once

#include "Exception.h"

/************************************************************************
* Class: Array<T>
*
* Purpose:
*		Provides a wrapper for a standard, dynamically allocated, one
*		dimensional array.
*
* Manager functions:
*		Array<T>()
*			Default ctor. Creates an array of length = 0.
*
*		Array<T>(int length, int start_index = 0)
*			Two arg ctor. Creates a array of specified length.
*
*		Array<T>(const Array & copy)
*			Copy ctor.
*
*		~Array<T>()
*			Destructor. Deallocates memory used for the array.
*
*		operator =(const Array & rhs)
*			Operator equals.
*
* Methods:
*		operator [](int index)
*			Returns the value held at 'index' of the array.
*
*		getStartIndex() const
*			Returns the current start index.
*
*		setStartIndex(int start_index)
*			Sets the start index to another value.
*
*		getLength() const
*			Returns the total length of the array.
*
*		setLength(int length)
*			Resizes the array to a new length.
*
*************************************************************************/

template<typename T>
class Array
{
public:
	Array<T>();
	Array<T>(int length, int start_index = 0);
	Array<T>(const Array & copy);
	~Array<T>();
	Array<T> & operator =(const Array & rhs);
	T & operator [](int index);

	int getStartIndex() const;
	void setStartIndex(int start_index);
	int getLength() const;
	void setLength(int length);

private:
	T * m_array;
	int m_length;
	int m_start_index;
};

/************************************************************************
* Purpose: Default ctor. Creates an array of length = 0.
*
* Precondition:
*		None.
*
* Postcondition:
*		All values set to their defaults.
*
************************************************************************/

template<typename T>
Array<T>::Array() : m_length(0), m_start_index(0), m_array(nullptr)
{
	m_array = new T[m_length];
}

/************************************************************************
* Purpose: Two arg ctor. Creates a array of specified length.
*
* Precondition:
*		length - The desired length of the array.
*		start_index - An alternative start index.
*
* Postcondition:
*		Creates the array and sets the start index to the desired value.
*
************************************************************************/

template<typename T>
Array<T>::Array(int length, int start_index = 0) : m_length(length), m_start_index(start_index), m_array(nullptr)
{
	m_array = new T[m_length];
}

/************************************************************************
* Purpose: Copy ctor.
*
* Precondition:
*		copy - An Array object.
*
* Postcondition:
*		Copies rhs into the current object.
*
************************************************************************/

template<typename T>
Array<T>::Array(const Array & copy) : m_length(copy.m_length), m_start_index(copy.m_start_index), m_array(nullptr)
{
	*this = copy;
}

/************************************************************************
* Purpose: Destructor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Deallocates memory used for the array.
*
************************************************************************/

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
}

/************************************************************************
* Purpose: Operator equals.
*
* Precondition:
*		rhs - An Array object.
*
* Postcondition:
*		Sets the current object equal to rhs.
*
************************************************************************/

template<typename T>
Array<T> & Array<T>::operator =(const Array & rhs)
{
	if (this != &rhs)
	{
		this->m_length = rhs.m_length;
		this->m_start_index = rhs.m_start_index;

		if (rhs.m_array != nullptr)
		{
			if (this->m_array != nullptr)
			{
				delete[] this->m_array;
				this->m_array = nullptr;
			}

			this->m_array = new T[this->m_length];

			for (int i = 0; i < this->m_length; i++)
				this->m_array[i] = rhs.m_array[i];
		}
	}

	return *this;
}

/************************************************************************
* Purpose: Returns the value held at 'index' of the array.
*
* Precondition:
*		index - The index of the desired data.
*
* Postcondition:
*		Returns the value held at 'index' of the array.
*
************************************************************************/

template<typename T>
T & Array<T>::operator [](int index)
{
	if (m_array != nullptr)
	{
		if (index >= m_start_index && index < m_start_index + m_length)
			return m_array[index - m_start_index];
		else
			throw Exception("Error! Index must be within the bounds of the array.");
	}
}

/************************************************************************
* Purpose: Returns the current starting index.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the current starting index.
*
************************************************************************/

template<typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

/************************************************************************
* Purpose: Sets the start_index to a new value.
*
* Precondition:
*		start_index - The new start index.
*
* Postcondition:
*		Sets m_start_index to start_index.
*
************************************************************************/

template<typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}

/************************************************************************
* Purpose: Returns the current length of the array.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the current length of the array.
*
************************************************************************/

template<typename T>
int Array<T>::getLength() const
{
	return m_length;
}

/************************************************************************
* Purpose: Resizes the array to a new length.
*
* Precondition:
*		length - The new length of the array.
*
* Postcondition:
*		Resizes the array to match the desired length.
*
************************************************************************/

template<typename T>
void Array<T>::setLength(int length)
{
	if (length < 0)
	{
		throw Exception("Error! Length cannot be less than zero.");
	}
	else if (length != m_length)
	{
		T * temp = new T[length];

		int len = (length < m_length) ? length : m_length;

		for (int i = 0; i < len; i++)
			temp[i] = m_array[i];

		delete[] m_array;
		m_array = temp;

		m_length = length;
	}
}