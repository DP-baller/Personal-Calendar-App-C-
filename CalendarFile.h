#pragma once
#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
using namespace std;

class CalendarFile
{
private:
	fstream myFile;
public:
	fstream getFile();
	void openFile();
	void addEvent(Date& date, string text);
	void deleteEvent(Date& date);
	void sortEvents();
	void reverseSortEvents();
	bool isEmpty();
	void emptyFile();
	void closeFile();
	void displayEvents();
	CalendarFile();
};