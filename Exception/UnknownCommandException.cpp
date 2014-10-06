#include "UnknownCommandException.h"

UnknownCommandException::UnknownCommandException()
{
    SetType("Unknown command exception");
    SetMessage("Unknown command exception");
    SetDebugMessage("Source filename and line are unknown");
    SetSourceLine(-1);
}

UnknownCommandException::UnknownCommandException(Exception *exception)
{
    SetType(exception->GetType());
    SetMessage(exception->GetMessage());
    SetDebugMessage(exception->GetDebugMessage());
    SetSourceFilename(exception->GetSourceFilename());
    SetSourceLine(exception->GetSourceLine());
}

UnknownCommandException::UnknownCommandException(QString message)
{
    UnknownCommandException();
    SetMessage(message);
}

UnknownCommandException::UnknownCommandException(QString message, QString type)
{
    UnknownCommandException();
    SetType(type);
    SetMessage(message);
}

UnknownCommandException::UnknownCommandException(QString message, QString sourceFilename, int sourceLine)
{
    UnknownCommandException();
    SetMessage(message);
    SetSourceFilename(sourceFilename);
    SetSourceLine(sourceLine);
}

UnknownCommandException::UnknownCommandException(QString message, QString sourceFilename, int sourceLine, QString type)
{
    UnknownCommandException();
    SetType(type);
    SetMessage(message);
    SetSourceFilename(sourceFilename);
    SetSourceLine(sourceLine);
}

UnknownCommandException::UnknownCommandException(UnknownCommandException const &exception)
{
    SetType(exception.GetType());
    SetMessage(exception.GetMessage());
    SetDebugMessage(exception.GetDebugMessage());
    SetSourceFilename(exception.GetSourceFilename());
    SetSourceLine(exception.GetSourceLine());
}

void UnknownCommandException::raise() const
{
    throw *this;
}

UnknownCommandException *UnknownCommandException::clone()
{
    return new UnknownCommandException(this);
}

UnknownCommandException::~UnknownCommandException()
{

}


