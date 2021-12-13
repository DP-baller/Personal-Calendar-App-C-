//==========================================================
//This is the header information
//
// Title:                Personal Calendar App
// Author:				 Dan Pop
// Date completed:       12/1/2021
// Description:
//	 There are way too many events to keep track in your head throughout our busy modern lives.
//   Dan's Personal Calendar App can help exactly that by recording them for you.
//	 Password protected, formatted output, user-friendly, you can store your important dates now.
//
//==========================================================
#include <cstdlib> // For several general-purpose functions
#include <fstream> // For file handling
#include <iomanip> // For formatted output
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
#include "Date.h" // Calendar class file
#include "exceptionHandling.h" // For error handling
#include "CalendarFile.h" // For Data storage to read and write
using namespace std; // So "std::cout" may be abbreviated to "cout"

void displayBorder()
{
	char line = 240;
	for (int i = 0; i < 100; i++)
		cout << line;
	cout << endl << endl;
}

void recordEvent(Date& date)
{
	CalendarFile myFile;
	myFile.openFile();
	string userInputText;
	cout << "Enter a description of the event: ";
	cin.ignore(1000, '\n');
	getline(cin, userInputText);
	myFile.addEvent(date, userInputText);
	cout << endl;
	cout << "Event recorded!" << endl;
	myFile.closeFile();
}

void verifyPassword()
{
	// create fstream file to store password for future reference
	fstream passwordFile;
	passwordFile.open("passwordStorage.txt", ios::in);

	// grab password string if it has been created yet
	string password;
	getline(passwordFile, password);

	// close file
	passwordFile.close();

	// check if password is nonexistent
	if (password.empty())
	{
		// open file to store a new password
		passwordFile.open("passwordStorage.txt", ios::out);

		// ask user for a password
		cout << "Create password: ";
		cin >> password;

		// password is stored into file
		passwordFile << password;

		// close file
		passwordFile.close();
	}
	// open file to grab password from then close
	passwordFile.open("passwordStorage.txt", ios::in);
	getline(passwordFile, password);
	passwordFile.close();

	// ask user for the password
	string userInput;
	cout << "Enter Password: ";
	cin >> userInput;

	// repeat for password until it is verified
	while (userInput != password)
	{
		cout << "Access denied." << endl << "Reenter password: ";
		cin >> userInput;
	}
	cout << "Access granted!" << endl;
	
	displayBorder();
}

int displayMenuOption()
{
	int userInputMenu;
	cout << "Which action would you like this program to perform?" << endl;
	cout << "\tPress [1] to display date on calendar." << endl;
	cout << "\tPress [2] to record an event in file." << endl;
	cout << "\tPress [3] to delete an event from file." << endl;
	cout << "\tPress [4] to display events from file." << endl;
	cout << "\tPress [5] to compare two dates." << endl;
	cout << "\tPress [6] to empty all events from file." << endl;
	cout << "\tPress [7] to sort all events in file." << endl;
	cout << "\tPress [9] to quit program." << endl;
	cin >> userInputMenu;
	return userInputMenu;
}

void executeProgram()
{
	int userInput;
	userInput = displayMenuOption();
	cout << endl;
	//Validation loop
	while (userInput != 9)
	{
		if (userInput == 1)
		{	
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//Input validations with error messages
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw exceptionHandling("ERROR: Invalid month value");
				else
				{
					date1.setMonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw exceptionHandling("ERROR: Invalid year value");
					else
					{
						date1.setYear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw exceptionHandling("ERROR: Invalid day value");
							else
							{
								//Display date1
								date1.setDay(userInputDay);
								cout << endl << date1 << endl;
								date1.displayCalendar();
							}
								
						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw exceptionHandling("ERROR: Invalid day value");
							else
							{
								//Display date1
								date1.setDay(userInputDay);
								cout << endl << date1 << endl;
								date1.displayCalendar();
							}
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									//Display date1
									date1.setDay(userInputDay);
									cout << endl << date1 << endl;
									date1.displayCalendar();
								}
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									//Display date1
									date1.setDay(userInputDay);
									cout << endl << date1 << endl;
									date1.displayCalendar();
								}
							}
						}
					}
				}		
			}
			catch (exceptionHandling errorObj)
			{
				cout << errorObj.what() << endl;
			}

			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 2)
		{
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//Input validations with error messages
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw exceptionHandling("ERROR: Invalid month value");
				else
				{
					date1.setMonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw exceptionHandling("ERROR: Invalid year value");
					else
					{
						date1.setYear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw exceptionHandling("ERROR: Invalid day value");
							else
							{
								date1.setDay(userInputDay);
								recordEvent(date1);
							}
						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw exceptionHandling("ERROR: Invalid day value");
							else
							{
								date1.setDay(userInputDay);
								recordEvent(date1);
							}
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date1.setDay(userInputDay);
									recordEvent(date1);
								}
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date1.setDay(userInputDay);
									recordEvent(date1);
								}
							}
						}
					}
				}
			}
			catch (exceptionHandling errorObj)
			{
				cout << errorObj.what() << endl;
			}
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 3)
		{
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//Input validations with error messages
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw exceptionHandling("ERROR: Invalid month value");
				else
				{
					date1.setMonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw exceptionHandling("ERROR: Invalid year value");
					else
					{
						date1.setYear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw exceptionHandling("ERROR: Invalid day value");
							else
								date1.setDay(userInputDay);
						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw exceptionHandling("ERROR: Invalid day value");
							else
								date1.setDay(userInputDay);
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw exceptionHandling("ERROR: Invalid day value");
								else
									date1.setDay(userInputDay);
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw exceptionHandling("ERROR: Invalid day value");
								else
									date1.setDay(userInputDay);
							}
						}
					}
				}
			}
			catch (exceptionHandling errorObj)
			{
				cout << errorObj.what() << endl;
			}
			CalendarFile myFile;
			myFile.deleteEvent(date1);
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 4)
		{
			CalendarFile myFile;
			myFile.displayEvents();
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 5)
		{
			// Declare 2 Date objects
			Date date1;
			Date date2;
			// Sentenial loops to retrieve dates without error
			// Sentenial loop keys
			bool userInputPass1 = false;
			bool userInputPass2 = false;
			while (userInputPass1 == false)
			{
				int userInputMonth, userInputDay, userInputYear;
				cout << "Enter first date(MM DD YYYY) seperate with spaces: ";
				cin >> userInputMonth >> userInputDay >> userInputYear;
				//Input validations with error messages
				try
				{
					if (userInputMonth < 1 || userInputMonth > 12)
						throw exceptionHandling("ERROR: Invalid month value");
					else
					{
						date1.setMonth(userInputMonth);
						if (userInputYear < 1583 || userInputYear > 9999)
							throw exceptionHandling("ERROR: Invalid year value");
						else
						{
							date1.setYear(userInputYear);
							if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
							{
								if (userInputDay < 1 || userInputDay > 31)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date1.setDay(userInputDay);
									userInputPass1 = true;
								}	
							}
							else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
							{
								if (userInputDay < 1 || userInputDay > 30)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date1.setDay(userInputDay);
									userInputPass1 = true;
								}
							}
							else if (userInputMonth == 2)
							{
								if (date1.isLeapYear() == true)
								{
									if (userInputDay < 1 || userInputDay > 29)
										throw exceptionHandling("ERROR: Invalid day value");
									else
									{
										date1.setDay(userInputDay);
										userInputPass1 = true;
									}
								}
								else if (date1.isLeapYear() == false)
								{
									if (userInputDay < 1 || userInputDay > 28)
										throw exceptionHandling("ERROR: Invalid day value");
									else
									{
										date1.setDay(userInputDay);
										userInputPass1 = true;
									}
								}
							}
						}
					}
				}
				catch (exceptionHandling errorObj)
				{
					cout << errorObj.what() << endl;
				}
			}	
			while (userInputPass2 == false)
			{
				int userInputMonth, userInputDay, userInputYear;
				cout << "Enter second date(MM DD YYYY) seperate with spaces: ";
				cin >> userInputMonth >> userInputDay >> userInputYear;
				//Input validations with error messages
				try
				{
					if (userInputMonth < 1 || userInputMonth > 12)
						throw exceptionHandling("ERROR: Invalid month value");
					else
					{
						date2.setMonth(userInputMonth);
						if (userInputYear < 1583 || userInputYear > 9999)
							throw exceptionHandling("ERROR: Invalid year value");
						else
						{
							date2.setYear(userInputYear);
							if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
							{
								if (userInputDay < 1 || userInputDay > 31)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date2.setDay(userInputDay);
									userInputPass2 = true;
								}
							}
							else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
							{
								if (userInputDay < 1 || userInputDay > 30)
									throw exceptionHandling("ERROR: Invalid day value");
								else
								{
									date2.setDay(userInputDay);
									userInputPass2 = true;
								}
							}
							else if (userInputMonth == 2)
							{
								if (date2.isLeapYear() == true)
								{
									if (userInputDay < 1 || userInputDay > 29)
										throw exceptionHandling("ERROR: Invalid day value");
									else
									{
										date2.setDay(userInputDay);
										userInputPass2 = true;
									}
								}
								else if (date2.isLeapYear() == false)
								{
									if (userInputDay < 1 || userInputDay > 28)
										throw exceptionHandling("ERROR: Invalid day value");
									else
									{
										date2.setDay(userInputDay);
										userInputPass2 = true;
									}
								}
							}
						}
					}
				}
				catch (exceptionHandling errorObj)
				{
					cout << errorObj.what() << endl;
				}
			}
			int compareDates = date1 > date2;

			cout << "First Date: " << date1 << endl;
			cout << "Second Date: " << date2 << endl;

			if (compareDates == 2)
				cout << "Dates are the same." << endl;

			int daysApart = date1 - date2;
			cout << "They are " << daysApart << " days apart." << endl;

			// Ask for userInput from menu
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 6)
		{
			char userInputChar;
			cout << "Are you sure you would like to empty your file? (y/n): ";
			cin >> userInputChar;
			while (userInputChar != 'y' && userInputChar != 'n')
			{
				cout << "(y/n): ";
				cin >> userInputChar;
			}
			if (userInputChar == 'y')
			{
				CalendarFile myFile;
				myFile.emptyFile();
			}
			displayBorder();
			// Ask for userInput from menu
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 7)
		{
			CalendarFile myFile;
			char userInputChar;
			cout << "How would you like to sort your events?\n\tPress [1] for chronological.\n\tPress [2] for reverse chronological.\n";
			cin >> userInputChar;
			while (userInputChar != '1' && userInputChar != '2')
			{
				cout << "(1 or 2): ";
				cin >> userInputChar;
			}
			if (userInputChar == '1')
				myFile.sortEvents();
			else if (userInputChar == '2')
				myFile.reverseSortEvents();
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else
		{
			// Ask for userInput from menu
			cout << userInput << " is not an option.  Please enter a number listed." << endl;
			userInput = displayMenuOption();
		}	
	}
	//App closer
	cout << "Calendar App terminated." << endl;
	displayBorder();
}

int main()
{
	//App header
	cout << "Welcome to Dan's Calendar App!" << endl;
	displayBorder();

	//call functions
	verifyPassword();
	executeProgram();
}