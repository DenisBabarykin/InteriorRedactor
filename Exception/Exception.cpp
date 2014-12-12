#include "Exception.h"

QString Exception::GetType() const
{
    return type;
}

QString Exception::GetMessage() const
{
    return message;
}

QString Exception::GetDebugMessage() const
{
    if (sourceLine == -1 || sourceFilename.isEmpty())
    {
        debugMessage = "Source filename and line are unknown.";
        return debugMessage;
    }

    debugMessage = "Exception was thrown from " + sourceFilename + " from " +
            sourceLine + " line.";

    return debugMessage;
}

QString Exception::GetSourceFilename() const
{
    return sourceFilename;
}

int Exception::GetSourceLine() const
{
    return sourceLine;
}

void Exception::SetType(QString type)
{
    this->type = type;
}

void Exception::SetMessage(QString message)
{
    this->message = message;
}

void Exception::SetDebugMessage(QString debugMessage)
{
    this->debugMessage = debugMessage;
}

void Exception::SetSourceFilename(QString sourceFilename)
{
    this->sourceFilename = sourceFilename;
}

void Exception::SetSourceLine(int sourceLine)
{
    this->sourceLine = sourceLine;
}

Exception::~Exception() throw()
{
    /*type.clear();
    message.clear();
    debugMessage.clear();
    sourceFilename.clear(); */
}
