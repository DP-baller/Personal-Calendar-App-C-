#pragma once
#include <string>
#include <iostream>
using namespace std;

class Date
{
private:
	int month = 1;
	int year = 2021;
	int day = 1;
	string text = "";
public:
	void setMonth(int m);
	void setDay(int d);
	void setYear(int y);
	void setText(string txt);
	string getText()const;
	string getMonth()const;
	int getMonthInt()const;
	int getYear()const;
	int getDay()const;
	bool isLeapYear()const;
	string getDayOfTheWeek();
	string displayDate();
	void displayCalendar();
	friend ostream& operator<<(ostream& osObject, Date& date);
	friend bool operator!=(const Date& date1, const Date& date2);
	friend int operator-(Date& date1, Date& date2);
	// The further in the future the date is, the greater the date is
	int operator>(const Date& otherDate);
	//bool operator=(const Date& otherDate);
	//constructors
	Date();
	Date(int m, int d, int y);
};