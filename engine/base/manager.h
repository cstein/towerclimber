#ifndef __MANAGER_H_
#define __MANAGER_H_

#include <string>

/*
 * Base class for all managers
 */

class Manager {
public:
    Manager();
    ~Manager();
    virtual void Start() = 0;
    virtual void Stop() = 0;

protected:
    std::string _confpath;
    std::string _confname;

    const char* _name;
};

#endif
