#pragma once
#include "Event.h"

class EventCollection
{
private:
	Event* events = new Event;
	unsigned int currentSize;
	unsigned int maxSize;
public:
	EventCollection();
	EventCollection(unsigned int cSize, unsigned int mSize);
	EventCollection(const EventCollection& other);
	EventCollection& operator=(const EventCollection& other);
	~EventCollection();

	void addEvent(const char* name, unsigned int year, unsigned int month, unsigned int day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes);
	void resize(unsigned int newSize);
	void deleteEvent(const char* name);
	char* longestEvent() const;
	unsigned int countOfMaxEventsForDate(unsigned int year, unsigned int month, unsigned int day) const;
	void printColection() const;
};