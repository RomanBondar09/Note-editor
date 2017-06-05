#pragma once
#include <deque>
#include <list>
#include "Note.h"
#include "Rest.h"

struct Pos
{
	int x, y;
};

class Bar
{
	int sizeBar;
	int numberOfNote;
    bool error;
	std::deque<NoteRest*> bufNote;
public:
	Bar();
	size_t getNumberNote();
	int duration();
    void addNote(int heightNote, size_t numberNote);
    void addRest(size_t numberNote);
    void deleteNote(size_t numberNote);
    void increaseDuration(size_t numberNote);
    void decreaseDuration(size_t numberNote);
	int getIndexDuration(size_t numberNote);
    void increaseHeight(size_t numberNote);
	void decreaseHeight(size_t numberNote);
    void setError(bool err);
    bool getError() const;
    void displaysError();
    void print();
};
