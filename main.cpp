#include "MainForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;

    // Установка стиля qdarkstyle
    QFile f(":qdarkstyle/style.qss");
    if (f.exists())
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

    w.show();
    w.MoveFrameToCenter(); // Центрируем форму

    return a.exec();
}
