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
    bool isExecute;

public:
    explicit CommandController(QObject *parent = 0);

    void Execute();

signals:
    void ExecutionStatusSignal(bool isExecute);

private slots:
    void ExecuteNext();

};

#endif // COMMANDCONTROLLER_H
