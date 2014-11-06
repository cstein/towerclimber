#include "glwindow.h"

#include "easyloggingpp/src/easylogging++.h"

GLWindow::GLWindow() {
    el::Logger* SDLWindowLogger = el::Loggers::getLogger("GLWindow");
}

GLWindow::~GLWindow() {
    el::Loggers::unregisterLogger("GLWindow");
}

void GLWindow::Start() {
    Start(640, 480);
}
void GLWindow::Start(int width, int height) {
    _width = width;
    _height = height;

    CLOG(INFO, "GLWindow") << "Creating window. W = " << width << " H = " << height;
    SDL_Init( SDL_INIT_VIDEO );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow( "GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if ( window != NULL ) {
        context = SDL_GL_CreateContext( window );
    }
}

void GLWindow::Swap() {
    SDL_GL_SwapWindow( window );
}

void GLWindow::Stop() {
    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
}
