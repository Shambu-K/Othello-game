#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "View/Observer.h"

/**
 * @brief This is the Subject base class. The model is derived from it. 
 * It is observed by the Observer class.
 * 
 */
class Subject
{
    virtual void registerObserver(Observer *observer) = 0;
    //virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif