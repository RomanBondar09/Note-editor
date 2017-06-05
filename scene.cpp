#include "scene.h"
#include "QDebug"
#define STEP_X 20
#define STEP_Y 3
#define STEP_STUFF 90
#define STARTING_POINT_X 80
#define STARTING_POINT_Y 50
#define END_POINT_X STARTING_POINT_X + 32 * STEP_X

Scene::Scene(string scoreName, QObject *parent):QGraphicsScene(parent), Score(scoreName)
{
	setup();
	createStuff(0);
	createStuff(1);

	cursor = addPixmap(pixCursor);
    cursor->setScale(0.5);
	cursor->setPos(STARTING_POINT_X, STARTING_POINT_Y + 6);

	insertImageBar(cursor->pos().x(), 0);
}

void Scene::setup()
{
	pixStuff.load("resource\\stuff.png");
	pixClef.load("resource\\clef.png");
	pixCursor.load("resource\\cursor.png");
	barLine.load("resource\\barLine.png");

	pixNote[0].load("resource\\note1.png");
	pixNote[1].load("resource\\note2.png");
	pixNote[2].load("resource\\note4.png");
	pixNote[3].load("resource\\note8.png");
	pixNote[4].load("resource\\note16.png");
	pixNote[5].load("resource\\note32.png");

	pixRest[0].load("resource\\rest1.png");
	pixRest[1].load("resource\\rest2.png");
	pixRest[2].load("resource\\rest4.png");
	pixRest[3].load("resource\\rest8.png");
	pixRest[4].load("resource\\rest16.png");
	pixRest[5].load("resource\\rest32.png");
}

void Scene::createStuff(int number)
{
	StuffClef *temp = new StuffClef;
	temp->stuff =  addPixmap(pixStuff);
	temp->clef = addPixmap(pixClef);

	temp->stuff->setPos(20, 50 + number * STEP_STUFF);
	temp->stuff->setScale(1.0);

	temp->clef->setPos(25, 30 + number * STEP_STUFF);
	temp->clef->setScale(0.2);
	stuffClef.push_back(temp);
}

void Scene::insertImageBar(size_t x, size_t line)
{
	Bar tempBar;
	vector<Bar>::iterator iter = bufBar.begin();
	bufBar.insert(iter + coordCursor.barNumber, tempBar);

	imageBar tempImageBar;
	tempImageBar.barLine = addPixmap(barLine);
	tempImageBar.pointBegin.x = x;
	tempImageBar.pointBegin.line = line;
	tempImageBar.barLine->setPos(x + STEP_X + 7, STARTING_POINT_Y + line * STEP_STUFF);

	vector<imageBar>::iterator iterImage = score.begin();
	score.insert(iterImage + coordCursor.barNumber, tempImageBar);
}

void Scene::moveBar(int direction)
{
	score[coordCursor.barNumber].barLine->moveBy(STEP_X * direction, 0);
	for (size_t j = coordCursor.noteNumber; j < score[coordCursor.barNumber].note.size(); ++j)
	{
		score[coordCursor.barNumber].note[j]->moveBy(STEP_X * direction, 0);
	}
	for (size_t i = coordCursor.barNumber + 1; i < bufBar.size() && (score[i].pointBegin.line == coordCursor.lineNumber); ++i)
	{
		score[i].barLine->moveBy(STEP_X * direction, 0);
		score[i].pointBegin.x += STEP_X * direction;
		for (size_t j = 0; j < score[i].note.size(); ++j)
		{
			score[i].note[j]->moveBy(STEP_X * direction, 0);
		}
	}
}

void Scene::moveCursor(int direction)
{
	switch (direction)
	{
	case moveLeft:
		if (coordCursor.noteNumber == 0)
		{
			if (coordCursor.barNumber > 0)
			{
				--coordCursor.barNumber;
				if (fullSizeOfBar())
					coordCursor.noteNumber = bufBar[coordCursor.barNumber].getNumberNote() - 1;
				else
					coordCursor.noteNumber = bufBar[coordCursor.barNumber].getNumberNote();
			}
		}
		else
		{
			if (coordCursor.noteNumber == bufBar[coordCursor.barNumber].getNumberNote() && !(fullSizeOfBar()))
				moveBar(-1);
			--coordCursor.noteNumber;
		}
		break;
	case moveRight:
		if ((coordCursor.noteNumber == bufBar[coordCursor.barNumber].getNumberNote() - 1) && fullSizeOfBar()
				|| coordCursor.noteNumber == bufBar[coordCursor.barNumber].getNumberNote() && !fullSizeOfBar())
		{
			++coordCursor.barNumber;
			if (coordCursor.barNumber == bufBar.size())
			{
				insertImageBar(score[coordCursor.barNumber - 1].pointBegin.x + (coordCursor.noteNumber + 2) * STEP_X,
						coordCursor.lineNumber);
			}
			coordCursor.noteNumber = 0;
		}
		else
		{

			++coordCursor.noteNumber;
			if (coordCursor.noteNumber == bufBar[coordCursor.barNumber].getNumberNote())
			{
				moveBar(1);
			}
		}
		if  (score[coordCursor.barNumber].barLine->x() > END_POINT_X)
		{
			score[coordCursor.barNumber].pointBegin.x = STARTING_POINT_X;
			++score[coordCursor.barNumber].pointBegin.line;
			for (int i = 0; i < score[coordCursor.barNumber].note.size(); ++i)
			{
				score[coordCursor.barNumber].note[i]->setPos(STARTING_POINT_X + STEP_X * i,
															 score[coordCursor.barNumber].note[i]->y() + STEP_STUFF);
			}
			score[coordCursor.barNumber].barLine->setPos(score[coordCursor.barNumber].pointBegin.x + (coordCursor.noteNumber+1)
					* STEP_X, STARTING_POINT_Y + score[coordCursor.barNumber].pointBegin.line * STEP_STUFF);
			++coordCursor.lineNumber;
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
	cursor->setPos(score[coordCursor.barNumber].pointBegin.x + coordCursor.noteNumber * STEP_X,
			STARTING_POINT_Y + score[coordCursor.barNumber].pointBegin.line * STEP_STUFF + (coordCursor.height + 2) * STEP_Y);
}

void Scene::addImageNote()
{
	addNote();
	if (coordCursor.noteNumber == score[coordCursor.barNumber].note.size())
	{
		QGraphicsPixmapItem *tempNote = addPixmap(pixNote[2]);
		tempNote->setScale(0.175);
		tempNote->setPos(cursor->x() + 2, cursor->y() - 19);
		score[coordCursor.barNumber].note.push_back(tempNote);
	}
	else
	{
		score[coordCursor.barNumber].note[coordCursor.noteNumber]->setPos(cursor->x() + 2, cursor->y() - 19);
	}
}

void Scene::deleteImageNote()
{
	deleteNote();
	score[coordCursor.barNumber].note[coordCursor.noteNumber]->hide();
	std::deque<QGraphicsPixmapItem*>::iterator iter = score[coordCursor.barNumber].note.begin();
	score[coordCursor.barNumber].note.erase(iter + coordCursor.noteNumber);
	if (coordCursor.noteNumber != bufBar[coordCursor.barNumber].getNumberNote())
		moveBar(-1);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up :
		moveCursor(moveUp);
        break;
    case Qt::Key_Down :
        moveCursor(moveDown);
        break;
    case Qt::Key_Left :
        moveCursor(moveLeft);
        break;
    case Qt::Key_Right :
        moveCursor(moveRight);
        break;
	case Qt::Key_Enter :
		addImageNote();
        break;
    case Qt::Key_Backspace :
		deleteImageNote();
        break;
	case Qt::Key_Minus :
		increaseDuration();
		score[coordCursor.barNumber].note[coordCursor.noteNumber]->setPixmap(pixNote[getIndexDuration()]);
		break;
	case Qt::Key_Plus :
		decreaseDuration();
		score[coordCursor.barNumber].note[coordCursor.noteNumber]->setPixmap(pixNote[getIndexDuration()]);
	}
}
