#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>
#include <QString>

class Exception : public QException
{
private:
    QString type;                 // Тип ошибки
    QString message;              // Сообщение с информацией об ошибке для пользователя
    mutable QString debugMessage; // Сообщение с отладочной инормацией с sourceFilename и sourceLine
    QString sourceFilename;       // Имя .cpp файла, в котором произошло исключение
    int sourceLine;               // Номер строки, в которой произошло исключение

public:
    QString GetType() const;
    QString GetMessage() const;
    QString GetDebugMessage() const;
    QString GetSourceFilename() const;
    int GetSourceLine() const;

    void SetType(QString type);
    void SetMessage(QString message);
    void SetDebugMessage(QString debugMessage);
    void SetSourceFilename(QString sourceFilename);
    void SetSourceLine(int sourceLine);

    ~Exception() throw();
};

#endif // EXCEPTION_H
