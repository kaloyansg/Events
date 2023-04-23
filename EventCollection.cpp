#include "EventCollection.h"

EventCollection::EventCollection()
{
	currentSize = 1;
	maxSize = 8;
	events = new Event[maxSize];
}

EventCollection::EventCollection(unsigned int curSize, unsigned int maxSize)
{
	Event* tempEvents = new(std::nothrow) Event[curSize];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}

	this->currentSize = curSize;
	this->events = tempEvents;
	this->maxSize = maxSize;
}

EventCollection::EventCollection(const EventCollection& other)
{
	if (this == &other) return;

	Event* tempEvents = new(std::nothrow) Event[other.currentSize];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}

	this->currentSize = other.currentSize;
	this->maxSize = other.maxSize;
	this->events = tempEvents;
	for (int i = 0; i < this->currentSize; i++)
	{
		this->events[i] = other.events[i];
	}
}

EventCollection& EventCollection::operator=(const EventCollection& other)
{
	if (this == &other) return *this;

	Event* tempEvents = new(std::nothrow) Event[other.currentSize];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}

	delete[] this->events;
	this->currentSize = other.currentSize;
	this->maxSize = other.maxSize;
	this->events = tempEvents;
	for (int i = 0; i < this->currentSize; i++)
	{
		this->events[i] = other.events[i];
	}

	return *this;
}

EventCollection::~EventCollection()
{
	delete[] events;
}

void EventCollection::resize(unsigned int newSize)
{
	Event* tempEvents = new(std::nothrow) Event[newSize];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}
	this->maxSize = newSize;

	for (size_t i = 0; i < this->currentSize; i++)
	{
		tempEvents[i] = this->events[i];
	}

	delete[] this->events;
	this->events = tempEvents;
}

void EventCollection::deleteEvent(const char* name)
{

	for (int i = 0; i < this->currentSize - 1; i++)
	{
		if (strcmp(this->events[i].getName(), name) == 0)
		{
			this->currentSize -= 1;
			this->events[i] = this->events[this->currentSize - 1];
			break;
		}

	}
	Event* tempEvents = new(std::nothrow) Event[this->maxSize];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}
	for (int i = 0; i < this->currentSize - 1; i++)
	{
		tempEvents[i] = this->events[i];
	}
	delete[] this->events;
	this->events = tempEvents;
}

char* EventCollection::longestEvent() const
{
	unsigned int indexOfLongestEvent;
	unsigned int timeOfLongestEventInMin = 0;
	unsigned int startTimeInMin;
	unsigned int endTimeInMin;
	char nameOfEvent[100];
	for (int i = 0; i < this->currentSize - 1; i++)
	{
		startTimeInMin = (this->events[i].getTimeBeg().getHours() * 60) + this->events[i].getTimeBeg().getMinutes();
		endTimeInMin = (this->events[i].getTimeEnd().getHours() * 60) + this->events[i].getTimeEnd().getMinutes();
		if (timeOfLongestEventInMin < endTimeInMin - startTimeInMin)
		{
			timeOfLongestEventInMin = endTimeInMin - startTimeInMin;
			indexOfLongestEvent = i;
		}
	}

	strcpy(nameOfEvent, this->events[indexOfLongestEvent].getName());
	return nameOfEvent;
}

unsigned int EventCollection::countOfMaxEventsForDate(unsigned int year, unsigned int month, unsigned int day) const
{
	unsigned int counter = 0;
	unsigned int counterEventsWeCanGo = 1;
	unsigned int minIndex = 0;
	unsigned int maxIndex = 0;

	for (int i = 0; i < this->currentSize - 1; i++)
	{
		if (this->events[i].getDate().getYear() == year &&
			this->events[i].getDate().getMonth() == month &&
			this->events[i].getDate().getDay() == day)
		{
			counter++;
		}
	}

	Event* tempEvents = new(std::nothrow) Event[counter];
	if (!tempEvents)
	{
		std::cerr << "Not enough memory!";
		return;
	}

	for (int i = 0; i < counter; i++)
	{
		if (this->events[i].getDate().getYear() == year &&
			this->events[i].getDate().getMonth() == month &&
			this->events[i].getDate().getDay() == day)
		{
			tempEvents[i] = this->events[i];
		}
	}

	for (int i = 0; i < counter - 1; i++)
	{
		for (int j = i + 1; j < counter; j++)
		{
			if (tempEvents[j].getTimeBeg().getHours() < tempEvents[i].getTimeBeg().getHours() ||
				tempEvents[maxIndex].getTimeEnd().getHours() <= tempEvents[i].getTimeBeg().getHours() &&
				tempEvents[maxIndex].getTimeEnd().getMinutes() < tempEvents[i].getTimeBeg().getMinutes())
			{
				std::swap(tempEvents[i], tempEvents[j]);
			}
		}

	}

	for (int i = 1; i < counter; i++)
	{
		if (tempEvents[maxIndex].getTimeEnd().getHours() < tempEvents[i].getTimeBeg().getHours() ||
			tempEvents[maxIndex].getTimeEnd().getHours() <= tempEvents[i].getTimeBeg().getHours() &&
			tempEvents[maxIndex].getTimeEnd().getMinutes() < tempEvents[i].getTimeBeg().getMinutes())
		{
			maxIndex = i;
			counterEventsWeCanGo++;
		}

	}
	delete[] tempEvents;
	return counterEventsWeCanGo;
}

void EventCollection::printColection() const
{
	for (int i = 0; i < this->currentSize - 1; i++)
	{
		this->events[i].printEvent();
	}
}


void EventCollection::addEvent(const char* name, unsigned int year, unsigned int month, unsigned int day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes)
{
	if (this->currentSize == this->maxSize)
	{
		resize(this->maxSize * 2);
	}

	Date currDate(year, month, day);
	Time currTimeBeg(startHour, startMinutes, 0);
	Time currTimeEnd(endHour, endMinutes, 0);
	Event currEvent(name, currDate, currTimeBeg, currTimeEnd);

	this->events[this->currentSize - 1] = currEvent;
	this->currentSize++;
}