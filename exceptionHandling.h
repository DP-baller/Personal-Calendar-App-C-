#pragma once
#include <string>
using namespace std;

class exceptionHandling
{
private:
	string message;
public:
	string what();
	exceptionHandling(string m = "ERROR: Invalid value. Try again.");
};