#ifndef OPENINGFILEEXCEPTION_H
#define OPENINGFILEEXCEPTION_H

#include "Exception.h"

class OpeningFileException : public Exception
{
public:
    OpeningFileException();
    OpeningFileException(QString filename);

    void raise() const;               // Бросить исключение
    OpeningFileException *clone(); // Создать копию
};

#endif // OPENINGFILEEXCEPTION_H
