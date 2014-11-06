#ifndef __SDLWINDOW_H_
#define __SDLWINDOW_H_

#include "SDL.h"

#include "manager.h"

class SDLWindow: public Manager {
public:
    SDLWindow();
    virtual ~SDLWindow();
    virtual void Start();
    virtual void Start(int width, int height);
    virtual void Stop();
    virtual void Swap();
    virtual int GetWidth();
    virtual int GetHeight();
protected:
    int _width;
    int _height;
    SDL_Window* window;
private:
    SDL_Surface* screen;
};

#endif
