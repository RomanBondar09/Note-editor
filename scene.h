#pragma once
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "score.h"
#include <deque>

struct StuffClef
{
	QGraphicsPixmapItem *stuff;
	QGraphicsPixmapItem *clef;
};

struct Point
{
	size_t x;
	size_t line;
};

struct imageBar
{
	Point pointBegin;
	QGraphicsPixmapItem* barLine;
	std::deque<QGraphicsPixmapItem*> note;
};

class Scene : public QGraphicsScene, public Score
{
	std::vector<StuffClef*> stuffClef;
    QGraphicsPixmapItem *cursor;
	std::vector<imageBar> score;

	QPixmap pixStuff, pixClef, pixCursor, barLine, pixNote[6], pixRest[6];
public:
    Scene(string scoreName, QObject *parent = 0);
	void setup();
	void setCursor();
	void insertImageBar(size_t x, size_t y);
	void moveBar(int direction);
	void moveCursor(int direction);
	void addImageNote();
	void deleteImageNote();
	void createStuff(int number);
    void keyPressEvent(QKeyEvent *event);
};
