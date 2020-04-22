/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			LinkedList.h
* Date Created:		01/12/2017
* Modifications:	None
************************************************************/
#pragma once

#include <iostream>
using std::cout;

#include "Node.h"
#include "Exception.h"

/************************************************************************
* Class: LinkedList<T>
*
* Purpose:
*		An implementation of a doubley-linked list.
*
* Manager functions:
*		LinkedList<T>()
*			Default ctor. Creates list with head and tail = nullptr.
*
*		LinkedList<T>(int data)
*			One arg ctor. Creates list with a node of data.
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
* Methods:
*		bool isEmpty() 
*			Returns true if the list is empty.
*
*		const T& First() 
*			Returns a reference to the data in the first element of the
*			list.
*
*		const T& Last() 
*			Returns a reference to the data in the last element of the
*			list.
*
*		void Prepend(T data)
*			Prepends a node to the list.
*
*		void Append(T data)
*			Appends a node to the list.
*
*		void Purge()
*			Deletes all nodes and resets the list.
*
*		void Extract(T data)
*			Deletes a single matching node to the passed in data.
*
*		void InsertAfter(T data, T exist_data)
*			Inserts a node after the matching passed data.
*
*		void InsertBefore(T data, T exist_data)
*			Inserts a node before the matching passed data.
*
*************************************************************************/

template<typename T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(T data);
	LinkedList(const LinkedList & copy);
	~LinkedList();
	LinkedList<T> & operator =(const LinkedList & rhs);

	bool isEmpty() const;
	T& First() const;
	T& Last() const;
	void Prepend(T data);
	void Append(T data);
	void Purge();
	void Extract(T data);
	void InsertAfter(T data, T exist_data);
	void InsertBefore(T data, T exist_data);

private:
	Node<T> * m_head;
	Node<T> * m_tail;
};

/************************************************************************
* Purpose: Default constructor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Creates a linked list with head and tail = nullptr.
*
************************************************************************/

template<typename T>
LinkedList<T>::LinkedList() : m_head(nullptr), m_tail(nullptr)
{
}

/************************************************************************
* Purpose: One arg constructor.
*
* Precondition:
*		data - The data to be inserted into the list.
*
* Postcondition:
*		Creates a list with a node containing the passed in data.
*
************************************************************************/

template<typename T>
LinkedList<T>::LinkedList(T data) : m_head(nullptr), m_tail(nullptr)
{
	Node<T> * nn = new Node<T>(data);

	m_head = nn;
	m_tail = nn;
}

/************************************************************************
* Purpose: Copy constructor.
*
* Precondition:
*		copy - The LinkedList object to be copied.
*
* Postcondition:
*		Copies the data in copy to the current object.
*
************************************************************************/

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & copy) : m_head(nullptr), m_tail(nullptr)
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
*		Deallocates all memory used for the list.
*
************************************************************************/

template<typename T>
LinkedList<T>::~LinkedList()
{
	Purge();
}

/************************************************************************
* Purpose: Operator equals
*
* Precondition:
*		rhs - The LinkedList object to be set equal to.
*
* Postcondition:
*		Sets the current object equal to rhs.
*
************************************************************************/

template<typename T>
LinkedList<T> & LinkedList<T>::operator =(const LinkedList & rhs)
{
	if (this != &rhs)
	{
		if (this->m_head != nullptr)
		{
			this->Purge();
		}

		if (rhs.m_head == nullptr)
		{
			this->m_head = nullptr;
		}
		else
		{
			Node<T> * rhs_travel = rhs.m_head;
			this->m_head = new Node<T>(rhs_travel->m_data);
			Node<T> * travel = this->m_head;

			while (rhs_travel != rhs.m_tail)
			{
				rhs_travel = rhs_travel->m_next;
				
				Node<T> * nn = new Node<T>(rhs_travel->m_data);
				nn->m_prev = travel;

				travel->m_next = nn;
				travel = travel->m_next;
			}

			this->m_tail = travel;
		}
	}

	return *this;
}

/************************************************************************
* Purpose: Returns true if the list is empty.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns true if m_head is nullptr, else false.
*
************************************************************************/

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return (m_head == nullptr);
}

/************************************************************************
* Purpose: Returns a reference to the data in the first element of the
*			list.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the reference of m_head->m_data.
*
************************************************************************/

template<typename T>
T& LinkedList<T>::First() const
{
	if (isEmpty())
		throw Exception("Error! Cannot access data from an empty list.");
	else
		return m_head->m_data;
}

/************************************************************************
* Purpose: Returns a reference to the data in the last element of the
*			list.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the reference of m_tail->m_data.
*
************************************************************************/

template<typename T>
T& LinkedList<T>::Last() const
{
	if (isEmpty())
		throw Exception("Error! Cannot access data from an empty list.");
	else
		return m_tail->m_data;
}

/************************************************************************
* Purpose: Prepends a node to the list.
*
* Precondition:
*		data - The data to be prepended.
*
* Postcondition:
*		Creates and prepends a node of data.
*
************************************************************************/

template<typename T>
void LinkedList<T>::Prepend(T data)
{
	Node<T> * nn = new Node<T>(data);
	nn->m_next = m_head;
	
	if (!isEmpty())
		m_head->m_prev = nn;
	else
		m_tail = nn;

	m_head = nn;
}

/************************************************************************
* Purpose: Appends a node to the list.
*
* Precondition:
*		data - The data to be appended.
*
* Postcondition:
*		Creates and appends a node of data.
*
************************************************************************/

template<typename T>
void LinkedList<T>::Append(T data)
{
	Node<T> * nn = new Node<T>(data);
	nn->m_prev = m_tail;

	if (!isEmpty())
		m_tail->m_next = nn;
	else
		m_head = nn;

	m_tail = nn;
}

/************************************************************************
* Purpose: Deletes all nodes and resets the list.
*
* Precondition:
*		None.
*
* Postcondition:
*		Removes all nodes and deallocates all memory used for the list. 
*
************************************************************************/

template<typename T>
void LinkedList<T>::Purge()
{
	if (m_head != nullptr)
	{
		Node<T> * travel = m_head;
		
		while (travel->m_next != nullptr)
		{
			travel = travel->m_next;
			delete travel->m_prev;
			travel->m_prev = nullptr;
		}

		m_head = nullptr;
		delete m_tail;
		m_tail = nullptr;
	}
}

/************************************************************************
* Purpose: Deletes a single matching node to the passed in data.
*
* Precondition:
*		data - The data to look for.
*
* Postcondition:
*		Removes a node containing data.
*
************************************************************************/

template<typename T>
void LinkedList<T>::Extract(T data)
{
	if (m_head != nullptr)
	{
		Node<T> * travel = m_head;

		while (travel != nullptr && travel->m_data != data)
			travel = travel->m_next;

		if (travel == nullptr)
			throw Exception("Error! The passed data was not found in this list.\n");
		else
		{
			if (travel == m_tail && travel == m_head)
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
			else if (travel == m_tail)
			{
				m_tail = travel->m_prev;
				m_tail->m_next = nullptr;
			}
			else if (travel == m_head)
			{
				m_head = travel->m_next;
				m_head->m_prev = nullptr;
			}
			else
			{
				travel->m_next->m_prev = travel->m_prev;
				travel->m_prev->m_next = travel->m_next;
			}

			delete travel;
			travel = nullptr;
		}
	}
}

/************************************************************************
* Purpose: Inserts a node after the matching passed data.
*
* Precondition:
*		data - The data to be inserted.
*		exist_data - The data to look for.
*
* Postcondition:
*		Inserts a node of data after the node of exist_data.
*
************************************************************************/

template<typename T>
void LinkedList<T>::InsertAfter(T data, T exist_data)
{
	if (m_head == nullptr)
	{
		throw Exception("Error! List is empty");
	}
	else
	{
		Node<T> * travel = m_head;

		while (travel != nullptr && travel->m_data != exist_data)
			travel = travel->m_next;

		if (travel == nullptr)
			throw Exception("Error! The passed data was not found in this list.");
		else
		{
			Node<T> * nn = new Node<T>(data);
			nn->m_prev = travel;
			nn->m_next = travel->m_next;
			if (travel == m_tail)
				m_tail = nn;

			travel->m_next->m_prev = nn;
			travel->m_next = nn;
		}
	}
}

/************************************************************************
* Purpose: Inserts a node before the matching passed data.
*
* Precondition:
*		data - The data to be inserted.
*		exist_data - The data to look for.
*
* Postcondition:
*		Inserts a node of data before the node of exist_data.
*
************************************************************************/

template<typename T>
void LinkedList<T>::InsertBefore(T data, T exist_data)
{
	if (m_head == nullptr)
	{
		throw Exception("Error! List is empty");
	}
	else 
	{
		Node<T> * travel = m_head;

		while (travel != nullptr && travel->m_data != exist_data)
			travel = travel->m_next;

		if (travel == nullptr)
			throw Exception("Error! The passed data was not found in this list.\n");
		else
		{
			Node<T> * nn = new Node<T>(data);
			nn->m_prev = travel->m_prev;
			nn->m_next = travel;
			if (travel == m_head)
				m_head = nn;

			travel->m_prev->m_next = nn;
			travel->m_prev = nn;
		}
	}
}