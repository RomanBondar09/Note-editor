#pragma once
#include "NoteRest.h"
#define THE_HIGHEST_NOTE 12
#define THE_LOWEST_NOTE -12

enum Accidentals
{
    doubleFlat = -2, flat, natural, sharp, doubleSharp
};

class Note : public NoteRest
{
    int height;
    Accidentals accidentals = natural;
public:
    Note(int heightNote);
	void setHeight(int heightNote);
    void increaseHeight();
    void decreaseHeight();
    void print();
    int type();
};
