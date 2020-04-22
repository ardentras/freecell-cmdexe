/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Stack.h
* Date Created:		02/02/2017
* Modifications:	None.
************************************************************/

#pragma once

#include "LinkedList.h"

/************************************************************************
* Class: Stack<T>
*
* Purpose:
*		Provides a wrapper for a stack around the LinkedList<T> class.
*
* Manager functions:
*		Stack<T>(int size)
*			One arg ctor. Creates a stack of size, size.
*
*		Stack<T>(const Array & copy)
*			Copy ctor.
*
*		~Stack<T>()
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
class ListStack
{
public:
	ListStack();
	ListStack(const ListStack & copy);
	~ListStack();
	ListStack<T> & operator =(const ListStack & rhs);

	void Push(T item);
	T Pop();
	T& Peek();
	int Size();
	bool isEmpty();

private:
	int m_num_elems;
	LinkedList<T> m_stack;
};

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
ListStack<T>::ListStack() : m_stack(), m_num_elems(0)
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
ListStack<T>::ListStack(const ListStack & copy) : m_stack(copy.m_stack), m_num_elems(copy.m_num_elems)
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
ListStack<T>::~ListStack()
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
ListStack<T> & ListStack<T>::operator =(const ListStack & rhs)
{
	if (this != &rhs)
	{
		this->m_stack = rhs.m_stack;
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
void ListStack<T>::Push(T item)
{
	m_stack.Prepend(item);
	m_num_elems++;
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
T ListStack<T>::Pop()
{
	if (m_num_elems == 0)
		throw Exception("Error! Stack underflow.");
	else
	{
		T temp = m_stack.First();
		m_stack.Extract(m_stack.First()); 
		m_num_elems--;

		return temp;
	}
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
T& ListStack<T>::Peek()
{
	if (m_num_elems == 0)
		throw Exception("Error! The current stack is empty.");
	else
		return m_stack.First();
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
int ListStack<T>::Size()
{
	return m_num_elems;
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
bool ListStack<T>::isEmpty()
{
	return (m_num_elems == 0);
}