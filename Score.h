#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <list>
#include "Bar.h"

using namespace std;

struct Coordinates_of_cursor
{
    size_t barNumber;
    size_t noteNumber;
	size_t lineNumber;
    int height;
};

struct TimeSignature
{
    int numerator;
    int denominator;
};

struct ChangeClef
{
    size_t numberBar;
    int clef;
};

struct ChangeKeySignature
{
    size_t numberBar;
    int keySignature;
};

struct ChangeTimeSignature
{
    size_t numberBar;
    TimeSignature timeSignature;
};

enum directionMove { moveLeft, moveRight, moveUp, moveDown };

class Score
{
protected:
    string name;
    Coordinates_of_cursor coordCursor;
    vector<Bar> bufBar;
    list<ChangeClef> bufClef;
    list<ChangeKeySignature> bufKeySignature;
    list<ChangeTimeSignature> bufTimeSignature;
private:
    template <typename T>
    typename list<T>::iterator findIterForList(size_t numberBar, list<T> list);
public:
    Score(string scoreName);
    void renameScore(string scoreName);
    void moveCursor(int direction);
    void addNote();
    void deleteNote();
    void addRest();
    void increaseDuration();
    void decreaseDuration();
	int getIndexDuration();
    void increaseHeight();
    void decreaseHeight();
	void insertBar();
    void deleteBar();
    void changeClef(int newClef);
    void changeKeySignature(int newKeySignature);
    void changeTimeSignature(TimeSignature newTimeSignature);
	bool fullSizeOfBar();
    void print();
    void save(string fname);
    void load(string fname);
};
