#ifndef SINGLETONFACADE_H
#define SINGLETONFACADE_H

#include "Facade.h"

class SingletonFacade
{
private:
    SingletonFacade();

public:
    static Facade *GetFacade();
};

#endif // SINGLETONFACADE_H
