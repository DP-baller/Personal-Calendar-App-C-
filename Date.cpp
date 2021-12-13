#include "Date.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "exceptionHandling.h"
using namespace std;

void Date::setMonth(int m)
{
	try
	{
		if (m < 1 || m > 12)
			throw exceptionHandling("ERROR: Invalid month value");
		else
			month = m;
	}
	catch (exceptionHandling errorObj)
	{
		cout << errorObj.what() << endl;
	}
}

void Date::setDay(int d)
{
	try
	{
		if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
		{
			if (d < 1 || d > 31)
				throw exceptionHandling("ERROR: Invalid day value");
			else
				day = d;
		}
		else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
		{
			if (d < 1 || d > 30)
				throw exceptionHandling("ERROR: Invalid day value");
			else
				day = d;
		}
		else if (month == 2)
		{
			if (isLeapYear() == true)
			{
				if (d < 1 || d > 29)
					throw exceptionHandling("ERROR: Invalid day value");
				else
					day = d;
			}
			else if (isLeapYear() == false)
			{
				if (d < 1 || d > 28)
					throw exceptionHandling("ERROR: Invalid day value");
				else
					day = d;
			}
		}
	}
	catch (exceptionHandling errorObj)
	{
		cout << errorObj.what() << endl;
	}
}

void Date::setYear(int y)
{
	try
	{
		if (y < 1583 || y > 9999)
			throw exceptionHandling("ERROR: Invalid year value");
		else
			year = y;
	}
	catch (exceptionHandling errorObj)
	{
		cout << errorObj.what() << endl;
	}
}

void Date::setText(string txt)
{
	text = txt;
}

string Date::getText()const
{
	return text;
}

string Date::getMonth()const
{
	const string monthName[12] =
	{ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return monthName[month - 1];
}

int Date::getMonthInt()const
{
	return month;
}

int Date::getYear()const
{
	return year;
}

int Date::getDay()const
{
	return day;
}

bool Date::isLeapYear()const
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

string Date::getDayOfTheWeek()
{
	const string daysOfTheWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	//Calculate Year code
		//Turn year into int array
	int yearArr[4];
	int y = this->getYear();
	for (int i = 3; i >= 0; i--)
	{
		yearArr[i] = y % 10;
		y /= 10;
	}
		//split array into two ints
		//YcYY
		//2021
		//Yc = 20 | YY = 21
	int Yc = 0;
	int YY = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			Yc *= 10;
			Yc += yearArr[i];
		}
		else if (i == 2 || i == 3)
		{
			YY *= 10;
			YY += yearArr[i];
		}
	}
		//Calculating century code
	if (Yc % 4 == 0)
		Yc = 0;
	else if (Yc % 4 == 1)
		Yc = 5;
	else if (Yc % 4 == 2)
		Yc = 3;
	else if (Yc % 4 == 3)
		Yc = 1;
	int Y7 = YY % 7;
	int Y4 = YY / 4;
	int Y = Yc + Y7 + Y4;

	//Calculate Day code
	int D = this->getDay() % 7;

	//Calculate Month code
	int monthCode[12] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	if (this->isLeapYear() == true)
	{
		monthCode[0] = 5;
		monthCode[1] = 1;
	}
	else if (this->isLeapYear() == false)
	{
		monthCode[0] = 6;
		monthCode[1] = 2;
	}
	int M = monthCode[this->month - 1];

	//Calculate and return theDayOfTheWeek from daysOfTheWeek string array
	string theDayOfTheWeek = daysOfTheWeek[(D + M + Y) % 7];
	return theDayOfTheWeek;
}

string Date::displayDate()
{
	string ordinal = "th";
	if ((day == 1) || (day == 21) || (day == 31))
		ordinal = "st";
	else if ((day == 2) || (day == 22))
		ordinal = "nd";
	else if ((day == 3) || (day == 23))
		ordinal = "rd";
	string sDay = to_string(getDay());
	string sYear = to_string(getYear());
	return getMonth() + " " + sDay + ordinal + ", " + sYear + " (" + getDayOfTheWeek() + ")";
}

void Date::displayCalendar()
{
	const int COLFMT1 = 14 + (getMonth().length() / 2);
	const int COLFMT2 = 14 - (getMonth().length() / 2);
	const int COLFMT3 = 4;
	const int COLFMT4 = 28;
	
	//Captialize month name
	string month_ = getMonth();
	transform(month_.begin(), month_.end(), month_.begin(), [](unsigned char c) {return toupper(c); });

	//Month header
	cout << setfill(char(175)) << setw(COLFMT1) << right << month_ << setfill(char(174)) << setw(COLFMT2) << left << char(174) << endl;

	//Days header
	string dayOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	for (int i = 0; i < 7; i++)
		cout << setfill(char(32)) << setw(COLFMT3) << left << dayOfTheWeek[i];
	cout << endl;
	
	//Calculate Year code
	//Turn year into int array
	int yearArr[4];
	int y = this->getYear();
	for (int i = 3; i >= 0; i--)
	{
		yearArr[i] = y % 10;
		y /= 10;
	}
	//split array into two ints
	//YcYY
	//2021
	//Yc = 20 | YY = 21
	int Yc = 0;
	int YY = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			Yc *= 10;
			Yc += yearArr[i];
		}
		else if (i == 2 || i == 3)
		{
			YY *= 10;
			YY += yearArr[i];
		}
	}
	//Calculating century code
	if (Yc % 4 == 0)
		Yc = 0;
	else if (Yc % 4 == 1)
		Yc = 5;
	else if (Yc % 4 == 2)
		Yc = 3;
	else if (Yc % 4 == 3)
		Yc = 1;
	int Y7 = YY % 7;
	int Y4 = YY / 4;
	int Y = Yc + Y7 + Y4;

	//Calculate Month code
	int monthCode[12] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	if (this->isLeapYear() == true)
	{
		monthCode[0] = 5;
		monthCode[1] = 1;
	}
	else if (this->isLeapYear() == false)
	{
		monthCode[0] = 6;
		monthCode[1] = 2;
	}
	int M = monthCode[this->month - 1];

	//Calculate firstDayOfMonthIndex
	//We can replace D simply with 1 because 1 is the first day of every month and 1 mod 7 equals 1
	int firstDayOfMonthIndex = (1 + M + Y) % 7;
	
	//Calculate lastDayOfMonthIndex
	int numberOfDaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		//Check if leap year
	if (this->isLeapYear() == true)
		numberOfDaysInMonth[1] = 29;
	else if (this->isLeapYear() == false)
		numberOfDaysInMonth[1] = 28;
	int lastDayOfMonthIndex = numberOfDaysInMonth[this->month - 1];
	//Because there is a difference in amounts for dayIndex and index, we need to take that into account, otherwise
	//the last of the days equal to the difference will be missing from the calendar
	lastDayOfMonthIndex += firstDayOfMonthIndex;

	//Display days of calendar
	int index = 1;
	int dayIndex = 1;
	for (int week = 1; week <= 6; week++)
	{
		while (index <= (week * 7))
		{
			if ((index <= firstDayOfMonthIndex) || (index > lastDayOfMonthIndex))
				cout << "    ";
			else
			{
				if (dayIndex <= 9)
				{
					if (this->getDay() == dayIndex)
						cout << "{" << dayIndex << "} ";
					else
						cout << " " << dayIndex << "  ";
				}
				else if (10 <= dayIndex)
				{
					if (this->getDay() == dayIndex)
						cout << "{" << dayIndex << "}";
					else
						cout << " " << dayIndex << " ";
				}
				dayIndex++;
			}
			index++;
		}
		cout << endl;
	}
}

ostream& operator<<(ostream& osObject, Date& date)
{
	string ordinal = "th";
	if ((date.getDay() == 1) || (date.getDay() == 21) || (date.getDay() == 31))
		ordinal = "st";
	else if ((date.getDay() == 2) || (date.getDay() == 22))
		ordinal = "nd";
	else if ((date.getDay() == 3) || (date.getDay() == 23))
		ordinal = "rd";
	osObject << date.getDayOfTheWeek() << ", " << date.getMonth() << " " << date.getDay() << ordinal << ", " << date.getYear();
	return osObject;
}

int Date::operator>(const Date& otherDate)
{
	// Trinary statement
	// 0 = false
	// 1 = true
	// 2 = equal/neither
	if (year > otherDate.year)
		return 1;//true
	else if (year == otherDate.year)
	{
		if (month > otherDate.month)
			return 1;//true
		else if (month == otherDate.month)
		{
			if (day > otherDate.day)
				return 1;//true
			else if (day == otherDate.day)
				return 2;//equal
			else
				return 0;//false
		}
		else
			return 0;//false
	}
	else
		return 0;//false
}
/*
bool Date::operator=(const Date& otherDate)
{
	if (month == otherDate.month)
	{
		if (day == otherDate.day)
		{
			if (year == otherDate.year)
				return true;
		}
	}
	else
		return false;
}
*/

bool operator!=(const Date& date1, const Date& date2)
{
	if (date1.getYear() == date2.getYear())
	{
		if (date1.getMonth() == date2.getMonth())
		{
			if (date1.getDay() == date2.getDay())
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

int operator-(Date& date1, Date& date2)
{
	Date olderDate;
	Date newerDate;
	int isOlder = date2 > date1;
	if (isOlder == 0)
	{
		olderDate = date2;
		newerDate = date1;
	}
	else if (isOlder == 1)
	{
		olderDate = date1;
		newerDate = date2;
	}
	else if (isOlder == 2)
		return 0;

	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysInt = olderDate.getDay();
	int monthsInt = olderDate.getMonthInt();
	int yearsInt = olderDate.getYear();
	int daysDifference = 0;
	while (olderDate != newerDate)
	{
		// Check for leap year
		if (olderDate.isLeapYear() == true)
			months[1] = 29;
		else
			months[1] = 28;

		daysInt++;
		daysDifference++;
		if (daysInt > months[monthsInt - 1])
		{
			daysInt = 1;
			olderDate.setDay(daysInt);
			monthsInt++;
			if (monthsInt > 12)
			{
				monthsInt = 1;
				olderDate.setMonth(monthsInt);
				yearsInt++;
				olderDate.setYear(yearsInt);
			}
			else
				olderDate.setMonth(monthsInt);
		}
		else
			olderDate.setDay(daysInt);
	}
	return daysDifference;
}

Date::Date()
{}

Date::Date(int m, int d, int y)
{
	if (y >= 1583 && y <= 9999)
		year = y;
	else
		year = 2021;
	if (m >= 1 && m <= 12)
		month = m;
	else
		month = 1;
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		if ((d >= 1) && (d <= 31))
			day = d;
		else
			day = 1;
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		if ((d >= 1) && (d <= 30))
			day = d;
		else
			day = 1;
	}
	else if (month == 2)
	{
		if (isLeapYear() == true)
		{
			if ((d >= 1) && (d <= 29))
				day = d;
			else
				day = 1;
		}
		else
		{
			if ((d >= 1) && (d <= 28))
				day = d;
			else
				day = 1;
		}
	}
}