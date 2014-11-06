#ifndef __MANAGER_H_
#define __MANAGER_H_

/*
 * Base class for all managers
 */

class Manager {
public:
    Manager();
    virtual void Start() = 0;
    virtual void Stop() = 0;
};

#endif
