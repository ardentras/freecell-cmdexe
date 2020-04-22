/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Node.h
* Date Created:		01/12/2017
* Modifications:	None
************************************************************/
#pragma once

template<typename T>
class LinkedList;

/************************************************************************
* Class: Queue<T>
*
* Purpose:
*		Implements a node for the LinkedList class.
*
* Manager functions:
*		LinkedList<T>(int size)
*			Default ctor. Creates node with m_data = data.
*
*		LinkedList<T>(const LinkedList & copy)
*			Copy ctor.
*
*		~LinkedList<T>()
*			Destructor.
*
*		operator =(const LinkedList & rhs)
*			Operator equals.
*
*************************************************************************/

template<typename T>
class Node
{
	friend class LinkedList<T>;

private:
	T m_data;
	Node * m_next;
	Node * m_prev;

	Node<T>(T data);
	Node<T>(const Node & copy);
	~Node<T>();
	Node & operator =(const Node & rhs);
};

/************************************************************************
* Purpose: One arg constructor.
*
* Precondition:
*		data - The data to save to the node.
*
* Postcondition:
*		Creates a node with data, data.
*
************************************************************************/

template<typename T>
Node<T>::Node(T data) : m_next(nullptr), m_prev(nullptr)
{
	m_data = data;
}

/************************************************************************
* Purpose: Copy constructor.
*
* Precondition:
*		copy - The Node object to be copied.
*
* Postcondition:
*		Copies the data of copy to the current object.
*
************************************************************************/

template<typename T>
Node<T>::Node(const Node & copy) : m_next(nullptr), m_prev(nullptr)
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
*		Dereferences memory linked to this node.
*
************************************************************************/

template<typename T>
Node<T>::~Node()
{
	this->m_next = nullptr;
	this->m_prev = nullptr;
}

/************************************************************************
* Purpose: Operator equals
*
* Precondition:
*		rhs - The Node object to be set equal to.
*
* Postcondition:
*		Copies the data from rhs to the current object.
*
************************************************************************/

template<typename T>
Node<T> & Node<T>::operator =(const Node & rhs)
{
	if (this != &rhs)
	{
		this->m_data = rhs.m_data;
		this->m_next = nullptr;
		this->m_prev = nullptr;
	}

	return *this;
}