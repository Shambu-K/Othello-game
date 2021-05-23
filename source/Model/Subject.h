#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "View/Observer.h"

class Subject
{
    virtual void registerObserver(Observer *observer) = 0;
    //virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif