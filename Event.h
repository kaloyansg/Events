#pragma once
#include "Date.h"
#include "Time.h"
#include <cstring>

class Event
{
	char* name;
	Date date;
	Time timeBeg;
	Time timeEnd;

public:
	Event();
	Event(const char* name, Date date, Time timeBeg, Time timeEnd);
	Event(const Event& other);
	Event& operator=(const Event& other);
	~Event();

	const char* getName() const;
	Date getDate() const;
	Time getTimeBeg() const;
	Time getTimeEnd() const;

	const char* getWeekDay() const;

	void printEvent() const;
};

