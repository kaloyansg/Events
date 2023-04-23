#include "Event.h"

#pragma warning(disable:4996)

Event::Event()
{
	char* tempName = new(std::nothrow) char[strlen("Event_Name") + 1];
	if (!tempName)
	{
		std::cerr << "Not enogh memory!";
		return;
	}
	strcpy(tempName, "Event_Name");

	this->name = tempName;
	Date defaultDate;
	this->date = defaultDate;
	Time defaultTime1;
	this->timeBeg = defaultTime1;
	Time dafaultTime2;
	this->timeEnd = dafaultTime2;
}

Event::Event(const char* name, Date date, Time timeBeg, Time timeEnd)
{
	char* tempName = new(std::nothrow) char[strlen(name) + 1];
	if (!tempName)
	{
		std::cerr << "Not enogh memory!";
		return;
	}
	strcpy(tempName, name);

	this->name = tempName;
	this->date = date;
	this->timeBeg = timeBeg;
	this->timeEnd = timeEnd;
}

Event::Event(const Event& other)
{
	if (this == &other) return;
	char* tempName = new(std::nothrow) char[strlen(other.name) + 1];
	if (!tempName)
	{
		std::cerr << "Not enogh memory!";
		return;
	}
	strcpy_s(tempName, strlen(other.name), other.name);
	this->name = tempName;
	this->date = other.date;
	this->timeBeg = other.timeBeg;
	this->timeEnd = other.timeEnd;
}

Event& Event::operator=(const Event& other)
{
	if (this == &other) return*this;
	char* tempName = new(std::nothrow) char[strlen(other.name) + 1];
	if (!tempName)
	{
		std::cerr << "Not enough memory!";
		return*this;
	}
	strcpy_s(tempName, strlen(other.name), other.name);
	delete[] this->name;
	this->name = tempName;
	this->date = other.date;
	this->timeBeg = other.timeBeg;
	this->timeEnd = other.timeEnd;
	return*this;
}

Event::~Event()
{
	delete[] this->name;
}

const char* Event::getName() const
{
	return this->name;
}

Date Event::getDate() const
{
	return this->date;
}

Time Event::getTimeBeg() const
{
	return this->timeBeg;
}

Time Event::getTimeEnd() const
{
	return this->timeEnd;
}

const char* Event::getWeekDay() const
{
	switch (this->date.getDayOfWeek())
	{
	case 0: return "Monday";
	case 1: return "Tuesday";
	case 2: return "Wednesday";
	case 3: return "Thursday";
	case 4: return "Friday";
	case 5: return "Saturday";
	case 6: return "Sunday";
	}
}

void Event::printEvent() const
{
	std::cout << "Event name: " << this->name << std::endl;
	std::cout << "Date: " << this->date.getDay() << "." << this->date.getMonth() << "." << this->date.getYear() << " (" << this->getWeekDay() << ")" << std::endl;

	/*switch (this->date.getDayOfWeek())
	{
	case 0: std::cout << "(Monday)" << std::endl; break;
	case 1: std::cout << "(Tuesday)" << std::endl; break;
	case 2: std::cout << "(Wednesday)" << std::endl; break;
	case 3: std::cout << "(Thursday)" << std::endl; break;
	case 4: std::cout << "(Friday)" << std::endl; break;
	case 5: std::cout << "(Saturday)" << std::endl; break;
	case 6: std::cout << "(Sunday)" << std::endl; break;
	}*/

	std::cout << "Starts at: " << this->timeBeg.getHours() << ":" << this->timeBeg.getMinutes() << std::endl;
	std::cout << "Ends at: " << this->timeEnd.getHours() << ":" << this->timeEnd.getMinutes() << std::endl;
}
