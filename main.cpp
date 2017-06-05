#include "mainwindow.h"
#include <QApplication>
#include "scene.h"
#include "score.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
	window.setGeometry(267, 50, 832, 624);
    window.show();
    return a.exec();
}
