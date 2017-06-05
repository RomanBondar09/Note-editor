#include <list>
#include "bar.h"
#include "score.h"
#include "mainwindow.h"
#include <QDebug>

Bar::Bar()
{
	numberOfNote = sizeBar = error = 0;
}

size_t Bar::getNumberNote()
{
	return bufNote.size();
}

int Bar::duration()
{
    sizeBar = 0;
    for (size_t i = 0; i < bufNote.size(); ++i)
    {
        sizeBar += bufNote[i]->getDuration();
    }
    return sizeBar;
}

void Bar::addNote(int heightNote, size_t numberNote)
{
	Note *tempNote = new Note(heightNote);
    if (numberNote == bufNote.size())
	{
		bufNote.push_back(tempNote);
    }
    else
	{
		tempNote->setDuration(bufNote[numberNote]->getDuration());
		bufNote[numberNote] = tempNote;
    }
}

void Bar::addRest(size_t numberRest)
{
	Rest *tempRest = new Rest;
    if (numberRest < bufNote.size())
    {
		bufNote.push_back(tempRest);
    }
    else
	{
		tempRest->setDuration(bufNote[numberRest]->getDuration());
		bufNote[numberRest] = tempRest;
    }
}

void Bar::deleteNote(size_t numberNote)
{
	std::deque<NoteRest*>::iterator iter = bufNote.begin();
	delete bufNote[numberNote];
	bufNote.erase(iter + numberNote);
	/*if ((*iter)->type())
		addRest(numberNote);*/
}

void Bar::increaseDuration(size_t numberNote)
{
    bufNote[numberNote]->increaseDuration();
}

void Bar::decreaseDuration(size_t numberNote)
{
    bufNote[numberNote]->decreaseDuration();
}

int Bar::getIndexDuration(size_t numberNote)
{
	return bufNote[numberNote]->getIndexDuration();
}

void Bar::increaseHeight(size_t numberNote)
{
    if (bufNote[numberNote]->type())
        bufNote[numberNote]->increaseHeight();
}

void Bar::decreaseHeight(size_t numberNote)
{
    if (bufNote[numberNote]->type())
        bufNote[numberNote]->decreaseHeight();
}

void Bar::setError(bool err)
{
    error = err;
}

bool Bar::getError() const
{
    return error;
}

void Bar::displaysError()
{

}

void Bar::print()
{
    for (size_t i = 0; i < bufNote.size(); ++i)
        bufNote[i]->print();
}
