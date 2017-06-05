#include <QGraphicsView>
#include "mainwindow.h"
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QGraphicsView *w = new QGraphicsView(this);
    w->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    w->setFixedSize( 732, 500 );
    w->move(50,50);
    drawScene = new Scene("qwe", w);
    w->setScene(drawScene);
    drawScene->setSceneRect(0, 0, 600, 200);
}

MainWindow::~MainWindow()
{

}
