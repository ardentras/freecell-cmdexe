/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Stack.h
* Date Created:		02/02/2017
* Modifications:	None.
************************************************************/

#pragma once

#include "Array.h"

/************************************************************************
* Class: Stack<T>
*
* Purpose:
*		Provides a wrapper for a stack around the Array<T> class.
*
* Manager functions:
*		Array<T>(int size)
*			One arg ctor. Creates a stack of size, size.
*
*		Array<T>(const Array & copy)
*			Copy ctor.
*
*		~Array<T>()
*			Destructor.
*
*		operator =(const Array & rhs)
*			Operator equals.
*
* Methods:
*		Push(T item)
*			Pushes item onto the top of the stack.
*
*		Pop()
*			Removes and returns the data from the top of the stack.
*
*		Peek()
*			Returns the element on the top of the stack but does not 
*			remove it.
*
*		Size()
*			Returns the number of items currently on the stack.
*
*		isEmpty()
*			Returns true if the stack is empty.
*
*		isFull()
*			Returns true if the stack is full.
*
*************************************************************************/

template<typename T>
class ArrStack
{
public:
	ArrStack();
	ArrStack(int size);
	ArrStack(const ArrStack & copy);
	~ArrStack();
	ArrStack<T> & operator =(const ArrStack & rhs);

	void Push(T item);
	T Pop();
	T& Peek();
	int Size();
	bool isEmpty();
	bool isFull();

private:
	int m_size;
	int m_num_elems;
	Array<T> m_stack;
};

/************************************************************************
* Purpose: Default ctor. Creates a stack of size, 14.
*
* Precondition:
*		None.
*
* Postcondition:
*		All values set to their defaults. Array created of size, 14.
*
************************************************************************/

template<typename T>
ArrStack<T>::ArrStack() : m_stack(Array<T>(13)), m_num_elems(-1), m_size(13)
{
}

/************************************************************************
* Purpose: One arg ctor. Creates a stack of size, size.
*
* Precondition:
*		size - The intended size of the stack.
*
* Postcondition:
*		All values set to their defaults. Array created of size, size.
*
************************************************************************/

template<typename T>
ArrStack<T>::ArrStack(int size) : m_stack(size), m_num_elems(-1), m_size(size)
{
}

/************************************************************************
* Purpose: Copy constructor.
*
* Precondition:
*		copy - The Stack object to be copied.
*
* Postcondition:
*		Copies copy into the current object.
*
************************************************************************/

template<typename T>
ArrStack<T>::ArrStack(const ArrStack & copy) : m_stack(copy.m_stack), m_num_elems(copy.m_num_elems), m_size(copy.m_size)
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
*		Deallocates memory used for Stack.
*
************************************************************************/

template<typename T>
ArrStack<T>::~ArrStack()
{
}

/************************************************************************
* Purpose: Operator equals.
*
* Precondition:
*		rhs - The Stack object to set the current object equal to.
*
* Postcondition:
*		Sets the current object equal to rhs.
*
************************************************************************/

template<typename T>
ArrStack<T> & ArrStack<T>::operator =(const ArrStack & rhs)
{
	if (this != &rhs)
	{
		this->m_stack = rhs.m_stack;
		this->m_size = rhs.m_size;
		this->m_num_elems = rhs.m_num_elems;
	}

	return *this;
}

/************************************************************************
* Purpose: Pushes item onto the top of the stack.
*
* Precondition:
*		item - The data to be pushed onto the stack.
*
* Postcondition:
*		Appends item to the array and increments the number of elements.
*
************************************************************************/

template<typename T>
void ArrStack<T>::Push(T item)
{
	if (m_num_elems == m_size - 1)
		throw Exception("Error! Stack overflow.");
	else
		m_stack[++m_num_elems] = item;
}

/************************************************************************
* Purpose: Removes and returns the data from the top of the stack.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the last element of the array and decrements the number
*		of elements.
*
************************************************************************/

template<typename T>
T ArrStack<T>::Pop()
{
	if (m_num_elems == -1)
		throw Exception("Error! Stack underflow.");
	else
		return m_stack[m_num_elems--];
}

/************************************************************************
* Purpose: Returns the element on the top of the stack but does not 
*			remove it.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the last element of the array.
*
************************************************************************/

template<typename T>
T& ArrStack<T>::Peek()
{
	if (m_num_elems == -1)
		throw Exception("Error! The current stack is empty.");
	else
		return m_stack[m_num_elems];
}

/************************************************************************
* Purpose: Returns the current number of elements held in the stack.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the value of m_num_elems.
*
************************************************************************/

template<typename T>
int ArrStack<T>::Size()
{
	return m_num_elems + 1;
}

/************************************************************************
* Purpose: Returns true if the stack is empty.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns true if the stack is empty.
*
************************************************************************/

template<typename T>
bool ArrStack<T>::isEmpty()
{
	return (m_num_elems == -1);
}

/************************************************************************
* Purpose: Returns true if the stack is full.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns true if the stack is full.
*
************************************************************************/

template<typename T>
bool ArrStack<T>::isFull()
{
	return (m_num_elems == m_size - 1);
}