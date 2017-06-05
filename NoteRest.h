#pragma once
#define NOTE 1
#define REST 0
#include <QGraphicsPixmapItem>

enum NoteDuration
{
    sixty_four_note = 1,
    thirty_second_note = 2,
    sixteenth_note = 4,
    eighth_note = 8,
    quarter_note = 16,
    half_note = 32,
    whole_note = 64
};

class NoteRest
{
protected:
	int duration;
public:
    NoteRest();
	void setDuration(int noteDuration);
    int getDuration();
	int getIndexDuration();
    void increaseDuration();
	void decreaseDuration();
	virtual void increaseHeight();
	virtual void decreaseHeight();
    virtual void print() = 0;
    virtual int type() = 0;
};
