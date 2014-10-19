#include "MainForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.show();
    w.MoveFrameToCenter(); // Центрируем форму

    return a.exec();
}
