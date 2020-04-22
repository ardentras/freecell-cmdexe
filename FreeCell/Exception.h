#pragma once

#include <ostream>
using std::ostream;

/************************************************************************
* Class: Exception
*
* Purpose:
*		Contains an error message that can be printed if this object is
*		thrown as an error.
*
* Manager functions:
*		Exception()
*			The default ctor.
*
*		Exception(char * message)
*			One arg ctor that sets the message to the passed value.
*
*		Exception(const Exception & copy);
*			Copy ctor.
*
*		~Exception();
*			De-allocates memory used for the message.
*
*		Exception & operator =(const Exception & rhs);
*			Creates a deep copy of the message.
*
* Methods:
*		char * getMessage() const;
*			Returns the message.
*
*		void setMessage(char * message);
*			Sets the message to the passed value.
*
*		friend ostream & operator <<(ostream & stream, const Exception & except)
*			Allows for the message to be directly output with the << op.
*
*************************************************************************/

class Exception
{
public:
	Exception();
	Exception(char * message);
	Exception(const Exception & copy);
	~Exception();
	Exception & operator =(const Exception & rhs);

	char * getMessage() const;
	void setMessage(char * message);

	friend ostream & operator <<(ostream & stream, const Exception & except)
	{
		return stream << except.m_message;
	}

private:
	char * m_message;
};