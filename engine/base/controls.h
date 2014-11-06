#ifndef __CONTROLS_H_
#define __CONTROLS_H_

#include <SDL.h>

#include "manager.h"
#include "scene.h"

/*
 * Takes care of reading and parsing controls.
 *
 */

class Controls : public Manager {
public:
    Controls();
    ~Controls();
    virtual void Start();
    virtual void Stop();
    void Update(Scene* scene);
    bool IsExitState();
private:
    bool _isexitstate;
    SDL_Event _event;
};

#endif
