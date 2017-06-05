#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <QDebug>
#include "Score.h"

Score::Score(string scoreName) :name(scoreName), coordCursor({ 0 })
{
    ChangeClef initialClef;
    ChangeKeySignature initialKeySignature;
    ChangeTimeSignature initialTimeSignature;
    initialClef.numberBar = initialKeySignature.numberBar = initialTimeSignature.numberBar = 0;
    initialClef.clef = 1;
    bufClef.push_front(initialClef);
    initialKeySignature.keySignature = 0;
    bufKeySignature.push_front(initialKeySignature);
    initialTimeSignature.timeSignature.numerator = initialTimeSignature.timeSignature.denominator = 4;
    bufTimeSignature.push_front(initialTimeSignature);
}

void Score::renameScore(string scoreName)
{
	name = scoreName;
}

void Score::moveCursor(int direction)
{
    switch (direction)
    {
    case moveLeft:
        if (coordCursor.noteNumber == 0)
        {
            if (coordCursor.barNumber > 0)
            {
                --coordCursor.barNumber;
				coordCursor.noteNumber = bufBar[coordCursor.barNumber].getNumberNote();
            }
        }
        else
            --coordCursor.noteNumber;
        break;
	case moveRight:
		if (coordCursor.noteNumber < bufBar[coordCursor.barNumber].getNumberNote() &&
			(fullSizeOfBar()))
            ++coordCursor.noteNumber;
        else
		{
            ++coordCursor.barNumber;
			coordCursor.noteNumber = 0;
			insertBar();
        }
        break;
    case moveUp:
        if (coordCursor.height < THE_HIGHEST_NOTE)
            ++coordCursor.height;
         break;
    case moveDown:
        if (coordCursor.height > THE_LOWEST_NOTE)
            --coordCursor.height;
        break;
	}
}

void Score::addNote()
{
    bufBar[coordCursor.barNumber].addNote(coordCursor.height, coordCursor.noteNumber);
}

void Score::deleteNote()
{
    bufBar[coordCursor.barNumber].deleteNote(coordCursor.noteNumber);
}

void Score::addRest()
{
    bufBar[coordCursor.barNumber].addRest(coordCursor.noteNumber);
}

void Score::increaseDuration()
{
    bufBar[coordCursor.barNumber].increaseDuration(coordCursor.noteNumber);
}

void Score::decreaseDuration()
{
    bufBar[coordCursor.barNumber].decreaseDuration(coordCursor.noteNumber);
}

int Score::getIndexDuration()
{
	return bufBar[coordCursor.barNumber].getIndexDuration(coordCursor.noteNumber);
}

void Score::increaseHeight()
{
    bufBar[coordCursor.barNumber].increaseHeight(coordCursor.noteNumber);
}

void Score::decreaseHeight()
{
    bufBar[coordCursor.barNumber].decreaseHeight(coordCursor.noteNumber);
}

void Score::insertBar()
{
	Bar tempBar;
    vector<Bar>::iterator iter = bufBar.begin();
    bufBar.insert(iter + coordCursor.barNumber, tempBar);
}

void Score::deleteBar()
{
    vector<Bar>::iterator iter = bufBar.begin();
    bufBar.erase(iter + coordCursor.barNumber--);
}

template <typename T>
typename list<T>::iterator Score::findIterForList(size_t numberBar, list<T> list_)
{
    int i = 0;
    list<T>::iterator iter;
    for (iter = list_.begin(); iter != list_.end(); ++iter, ++i)
    {
        if (iter->numberBar > numberBar)
            break;
    }
    return iter;
}

void Score::changeClef(int newClef)
{
    list<ChangeClef>::iterator iter;
    ChangeClef tempClef;
    tempClef.clef = newClef;
    tempClef.numberBar = coordCursor.barNumber;
    iter = findIterForList<ChangeClef>(coordCursor.barNumber, bufClef);
    bufClef.insert(iter, tempClef);
}

void Score::changeKeySignature(int newKeySignature)
{
    list<ChangeKeySignature>::iterator iter;
    ChangeKeySignature tempKeySignature;
    iter = findIterForList<ChangeKeySignature>(coordCursor.barNumber, bufKeySignature);
    tempKeySignature.keySignature = newKeySignature;
    tempKeySignature.numberBar = coordCursor.barNumber;
    bufKeySignature.insert(iter, tempKeySignature);
}

void Score::changeTimeSignature(TimeSignature newTimeSignature)
{
    list<ChangeTimeSignature>::iterator iter;
    ChangeTimeSignature tempTimeSignature;
    iter = findIterForList<ChangeTimeSignature>(coordCursor.barNumber, bufTimeSignature);
    tempTimeSignature.timeSignature = newTimeSignature;
    tempTimeSignature.numberBar = coordCursor.barNumber;
    bufTimeSignature.insert(iter, tempTimeSignature);
}

bool Score::fullSizeOfBar()
{
    bool err;
    size_t fullSize;
	list<ChangeTimeSignature>::iterator iter;
	for (iter = bufTimeSignature.begin(); (iter != bufTimeSignature.end()) && (iter->numberBar <= coordCursor.barNumber); ++iter)
	{}
	--iter;
    fullSize = iter->timeSignature.numerator * 64 / iter->timeSignature.denominator;
	err = fullSize == (bufBar[coordCursor.barNumber].duration()) ? true : false;
    bufBar[coordCursor.barNumber].setError(err);
	return err;
}

void Score::print()
{
    for (size_t i = 0; i < bufBar.size(); ++i)
    {
        bufBar[i].print();
        cout << "|";
    }
}

void Score::save(string fname)
{
    ofstream outfile(fname, ios::binary);
    outfile << bufClef.size();

    outfile << bufKeySignature.size();

    outfile << bufTimeSignature.size();

    outfile << bufBar.size();

    outfile.close();
}

void Score::load(string fname)
{
    size_t sizeList;
    ChangeClef tempClef;
    ChangeKeySignature tempKeySignature;
    ChangeTimeSignature tempTimeSignature;
	Bar tempBar;
    ifstream infile(fname, ios::binary);
    name = fname;
    bufClef.clear();
    bufKeySignature.clear();
    bufTimeSignature.clear();
    infile >> sizeList;
    for(size_t i = 0; i < sizeList; ++i)
    {

        bufClef.push_back(tempClef);
    }
    infile >> sizeList;
    for(size_t i = 0; i < sizeList; ++i)
    {

        bufKeySignature.push_back(tempKeySignature);
    }
    infile >> sizeList;
    for(size_t i = 0; i < sizeList; ++i)
    {

        bufTimeSignature.push_back(tempTimeSignature);
    }
    infile >> sizeList;
    for(size_t i = 0; i < sizeList; ++i)
    {

        bufBar.push_back(tempBar);
    }
    infile.clear();
}
