#ifndef __GLWINDOW_H_
#define __GLWINDOW_H_

#include "sdlwindow.h"

#include <Eigen/Core>
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
    const inline Eigen::Matrix4f GetProjection() { return _projectionmatrix; }
private:
    SDL_GLContext context;
    Eigen::Matrix4f _projectionmatrix;
};

#endif
