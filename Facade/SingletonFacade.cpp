#include "SingletonFacade.h"

SingletonFacade::SingletonFacade()
{
}

Facade *SingletonFacade::GetFacade()
{
    static Facade facade;
    return &facade;
}
