#include "CalendarFile.h"
#include "exceptionHandling.h" // For Error control flow
#include <iostream>
#include <iomanip> // For formatted output
#include <vector> // For vector handling purposes
#include <sstream> // For file reading purposes

const int COLFMT1 = 40;
const int COLFMT2 = 60;

fstream CalendarFile::getFile()
{
    fstream myFile("Events.txt");
    return myFile;
}

void CalendarFile::openFile()
{
    // Open file to append mode (read and write)
    myFile.open("Events.txt", ios::app);
    // Check for error
    if (!myFile.is_open())
        cout << "ERROR: Unable to open file." << endl;
    else
        cout << "Successfully opened File." << endl;
}  

void CalendarFile::addEvent(Date& date, string text)
{
    myFile << setw(COLFMT1) << left << date.displayDate() << setw(COLFMT2) << left << text << '\n';
}

void CalendarFile::closeFile()
{
    if (!myFile.is_open())
        cout << "ERROR: File not open." << endl;
    else
    {
        myFile.close();
        cout << "File saved and closed." << endl;
    }
}

void CalendarFile::emptyFile()
{
    // Open file to truncate mode
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();
    cout << "All content erased!" << endl;
}

bool CalendarFile::isEmpty()
{
    if (!getFile())
        return 0;
    bool is_Empty = getFile().peek() == EOF;
    return is_Empty;
}

void CalendarFile::displayEvents()
{
    // Check if file is empty
    if (isEmpty() == true)
        cout << "There is no data to display." << endl;
    else if (isEmpty() == false)
    {
        // Display header
        cout << setw(40) << left << "Date" << setw(60) << left << "Description" << endl;
        cout << "====================================================================================================" << endl;
        // Display all content from file
        myFile.open("Events.txt", std::ofstream::in);
        if (myFile.is_open())
            cout << myFile.rdbuf();
        // Close file
        myFile.close();
        cout << endl;
    }
}

void CalendarFile::sortEvents()
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    //Temp storage line by line content to be translated
    vector<string> translateVect;
    Date dateFromFile;
    string description;
    //Storage for all events grabbed from file to be bubble sorted
    vector<Date> dates;

    //Translate and store content from file into a readable vector
    myFile.open("Events.txt");
    //Read file line by line
    string line;
    while (getline(myFile, line))
    {
        //Read line word by word
        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setMonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setDay(stoi(extractDay));

        dateFromFile.setYear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.setText(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    //Bubble sort dates chronologically
    Date temp;
    for (int passes = 1; passes < dates.size(); passes++)
    {
        for (int index = 0; index < dates.size() - passes; index++)
        {
            if (dates.at(index) > dates.at(index + 1))
            {
                temp = dates.at(index);
                dates.erase(dates.begin() + index);
                dates.insert(dates.begin() + index + 1, temp);
            }
        }
    }
    myFile.close();

    //Empty file
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();

    //Input sorted events into file
    myFile.open("Events.txt", ios::app);
    for (int i = 0; i < dates.size(); i++)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].getText() << endl;
    myFile.close();
    cout << "\nAll events are sorted!" << endl;
}

void CalendarFile::reverseSortEvents()
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    //Temp storage line by line content to be translated
    vector<string> translateVect;
    Date dateFromFile;
    string description;
    //Storage for all events grabbed from file to be bubble sorted
    vector<Date> dates;

    //Translate and store content from file into a readable vector
    myFile.open("Events.txt");
    //Read file line by line
    string line;
    while (getline(myFile, line))
    {
        //Read line word by word
        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setMonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setDay(stoi(extractDay));

        dateFromFile.setYear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.setText(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    //Bubble sort dates chronologically
    Date temp;
    for (int passes = 1; passes < dates.size(); passes++)
    {
        for (int index = 0; index < dates.size() - passes; index++)
        {
            if (dates.at(index) > dates.at(index + 1))
            {
                temp = dates.at(index);
                dates.erase(dates.begin() + index);
                dates.insert(dates.begin() + index + 1, temp);
            }
        }
    }
    myFile.close();

    //Empty file
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();

    //Input reverse sorted events into file
    myFile.open("Events.txt", ios::app);
    for (int i = dates.size() - 1; i >= 0; i--)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].getText() << endl;
    myFile.close();
    cout << "\nAll events are sorted!" << endl;
}

void CalendarFile::deleteEvent(Date& date)
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    //Temp storage line by line content to be translated
    vector<string> translateVect;
    Date dateFromFile;
    string description;
    //Storage for all events grabbed from file to be bubble sorted
    vector<Date> dates;

    //Translate and store content from file into a readable vector
    myFile.open("Events.txt");
    //Read file line by line
    string line;
    while (getline(myFile, line))
    {
        //Read line word by word
        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setMonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setDay(stoi(extractDay));

        dateFromFile.setYear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.setText(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    int equal;
    for (int index = 0; index < dates.size(); index++)
    {
        equal = date > dates.at(index);
        if (equal == 2)
            dates.erase(dates.begin() + index);
    }

    myFile.close();

    //Empty file
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();

    //Input events excluding selected into file
    myFile.open("Events.txt", ios::app);
    for (int i = 0; i < dates.size(); i++)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].getText() << endl;
    myFile.close();
    cout << "Event(s) successfully removed from file!" << endl;
}

CalendarFile::CalendarFile() {};