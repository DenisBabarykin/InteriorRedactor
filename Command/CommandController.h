#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QList>
#include "Command.h"

class CommandController : public QObject
{
    Q_OBJECT
private:
    QList<Command *> commandQueue;
    bool canExecute;

public:
    explicit CommandController(QObject *parent = 0);

    bool CanExecute();

signals:

public slots:

};

#endif // COMMANDCONTROLLER_H
