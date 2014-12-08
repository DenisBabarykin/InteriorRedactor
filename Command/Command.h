#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    virtual Execute() = 0;
    virtual ~Command() = 0;

};

#endif // COMMAND_H
