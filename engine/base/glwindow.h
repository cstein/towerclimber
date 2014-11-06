#ifndef __GLWINDOW_H_
#define __GLWINDOW_H_

#include "sdlwindow.h"

#include <GL/glew.h>
#include <SDL_opengl.h>

class GLWindow : public SDLWindow {
public:
    GLWindow();
    ~GLWindow();
    virtual void Start();
    virtual void Start(int width, int height);
    virtual void Stop();
    virtual void Swap();
private:
    SDL_GLContext context;
};

#endif
