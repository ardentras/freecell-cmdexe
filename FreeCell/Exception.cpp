/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Exception.cpp
* Date Created:		01/10/2017
* Modifications:	
*					01/20/2017 - Added documentation.
************************************************************/

#include "Exception.h"

/************************************************************************
* Purpose: Creates an Exception object with default parameters.
*
* Precondition:
*		None.
*
* Postcondition:
*		Creates an Exception object with default parameters.
*
************************************************************************/

Exception::Exception() : m_message(nullptr)
{
}

/************************************************************************
* Purpose: Creates an Exception object with the specified error message.
*
* Precondition:
*		message - A cstring containing the desired error message.
*
* Postcondition:
*		Creates an Exception object with the specified error message.
*
************************************************************************/

Exception::Exception(char * message) : m_message(nullptr)
{
	m_message = new char[strlen(message) + 1];
	strcpy_s(m_message, strlen(message) + 1, message);
}

/************************************************************************
* Purpose: Copy constructor for the Exception class.
*
* Precondition:
*		copy - An Exception object reference.
*
* Postcondition:
*		Copies one Exception object into a new one.
*
************************************************************************/

Exception::Exception(const Exception & copy) : m_message(nullptr)
{
	*this = copy;
}

/************************************************************************
* Purpose: Destructor for the Exception class.
*
* Precondition:
*		None.
*
* Postcondition:
*		De-allocates memory used for the error message.
*
************************************************************************/

Exception::~Exception()
{
	delete[] m_message;
	m_message = nullptr;
}

/************************************************************************
* Purpose: Sets the current object equal to the passed object.
*
* Precondition:
*		rhs - An Exception object reference.
*
* Postcondition:
*		Copies the information from rhs into the current object.
*
************************************************************************/

Exception & Exception::operator =(const Exception & rhs)
{
	if (this != &rhs)
	{
		if (this->m_message != nullptr)
		{
			delete[] this->m_message;
			this->m_message = nullptr;
		}
		this->m_message = new char[strlen(rhs.m_message) + 1];
		strcpy_s(this->m_message, strlen(rhs.m_message) + 1, rhs.m_message);
	}

	return *this;
}

/************************************************************************
* Purpose: Returns the error message.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the error message.
*
************************************************************************/

char * Exception::getMessage() const
{
	return m_message;
}

/************************************************************************
* Purpose: Sets the error message.
*
* Precondition:
*		message - A cstring containing the new message.
*
* Postcondition:
*		Sets the error message.
*
************************************************************************/

void Exception::setMessage(char * message)
{
	if (m_message != nullptr)
	{
		delete[] m_message;
		m_message = nullptr;
	}

	m_message = new char[strlen(message) + 1];
	strcpy_s(m_message, strlen(message) + 1, message);
}