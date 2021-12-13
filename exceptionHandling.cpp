#include "exceptionHandling.h"

string exceptionHandling::what()
{
	return message;
}

exceptionHandling::exceptionHandling(string m)
{
	message = m;
}