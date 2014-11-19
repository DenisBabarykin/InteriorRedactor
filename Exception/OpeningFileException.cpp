#include "OpeningFileException.h"

OpeningFileException::OpeningFileException()
{
    SetMessage("Opening file error");
}

OpeningFileException::OpeningFileException(QString filename)
{
    SetMessage("Opening file " + filename + " error");
}

void OpeningFileException::raise() const
{
    throw *this;
}

OpeningFileException *OpeningFileException::clone()
{
    return new OpeningFileException();
}
