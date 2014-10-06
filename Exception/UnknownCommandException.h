#ifndef UNKNOWNCOMMANDEXCEPTION_H
#define UNKNOWNCOMMANDEXCEPTION_H

#include "Exception.h"

class UnknownCommandException : public Exception
{
public:
    UnknownCommandException();
    explicit UnknownCommandException(Exception *exception);
    explicit UnknownCommandException(QString message);
    UnknownCommandException(QString message, QString type);
    UnknownCommandException(QString message, QString sourceFilename, int sourceLine);
    UnknownCommandException(QString message, QString sourceFilename, int sourceLine, QString type);

    UnknownCommandException(UnknownCommandException const &exception);

    void raise() const;               // Бросить исключение
    UnknownCommandException *clone(); // Создать копию

    ~UnknownCommandException();
};

#endif // UNKNOWNCOMMANDEXCEPTION_H
