

#include "SimpleString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static const int DEFAULT_SIZE = 20;

SimpleString::SimpleString ()
: buffer(new char [1])
{
	buffer [0] = '\0';
}


SimpleString::SimpleString (const char *otherBuffer)
: buffer (new char [strlen (otherBuffer) + 1])
{
	strcpy_s(buffer, strlen(otherBuffer) + 1, otherBuffer);
}

SimpleString::SimpleString (const SimpleString& other)
{
	buffer = new char [other.size() + 1];
	strcpy_s(buffer, other.size() + 1, other.buffer);
}


SimpleString SimpleString::operator= (const SimpleString& other)
{
	delete buffer;
	buffer = new char [other.size() + 1];
	strcpy_s(buffer, other.size() + 1, other.buffer);
	return *this;
}


char *SimpleString::asCharString () const
{
	return buffer;
}

int SimpleString::size() const
{
	return static_cast<int>(strlen (buffer));
}

SimpleString::~SimpleString ()
{
	delete [] buffer;
}


bool operator== (const SimpleString& left, const SimpleString& right)
{
	return !strcmp (left.asCharString (), right.asCharString ());
}


SimpleString StringFrom (bool value)
{
	char buffer [sizeof ("false") + 1];
	sprintf_s(buffer, "%s", value ? "true" : "false");
	return SimpleString(buffer);
}

SimpleString StringFrom (const char *value)
{
	return SimpleString(value);
}

SimpleString StringFrom (long value)
{
	char buffer [DEFAULT_SIZE];
	sprintf_s(buffer, "%ld", value);

	return SimpleString(buffer);
}

SimpleString StringFrom (double value)
{
	char buffer [DEFAULT_SIZE];
	sprintf_s(buffer, "%lf", value);

	return SimpleString(buffer);
}

SimpleString StringFrom (const SimpleString& value)
{
	return SimpleString(value);
}
