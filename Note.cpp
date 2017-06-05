#include "note.h"
#include <iostream>

Note::Note(int noteHeight)
{
	height = noteHeight;
}

void Note::increaseHeight()
{
    if (height < THE_HIGHEST_NOTE)
        ++height;
}

void Note::decreaseHeight()
{
    if (height < THE_HIGHEST_NOTE)
        --height;
}

void Note::print()
{
    for (size_t i = duration; i > 0; i >>= 1)
        std::cout << "*";
}

int Note::type()
{
    return NOTE;
}
