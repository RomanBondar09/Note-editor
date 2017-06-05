#include <QDebug>
#include "NoteRest.h"

NoteRest::NoteRest() :duration(16)
{}

void NoteRest::setDuration(int noteDuration)
{
    duration = noteDuration;
}

int NoteRest::getDuration()
{
    return duration;
}

int NoteRest::getIndexDuration()
{
	int i = duration, j;
	for (j = 0; i < 64; ++j, i <<= 1)
	{}
	return j;
}

void NoteRest::increaseDuration()
{
    if (duration < 64)
        duration <<= 1;
}

void NoteRest::decreaseDuration()
{
    if (duration > 1)
        duration >>= 1;
}

void NoteRest::increaseHeight()
{}

void NoteRest::decreaseHeight()
{}
