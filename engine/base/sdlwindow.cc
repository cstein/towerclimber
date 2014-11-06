#include "sdlwindow.h"

#include "easyloggingpp/src/easylogging++.h"

SDLWindow::SDLWindow() {
    el::Logger* SDLWindowLogger = el::Loggers::getLogger("SDLWindow");
}

SDLWindow::~SDLWindow() {
    CLOG(INFO, "SDLWindow") << "Bye.";
    el::Loggers::unregisterLogger("SDLWindow");
}

void SDLWindow::Start() {
    Start(640, 480);
}

void SDLWindow::Start(int width, int height) {
    _width = width;
    _height = height;

    CLOG(INFO, "SDLWindow") << "Creating window. W = " << width << " H = " << height;

    SDL_Init( SDL_INIT_VIDEO );
    window = SDL_CreateWindow( "GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if ( window != NULL ) {
        screen = SDL_GetWindowSurface( window );
        if ( screen == NULL ) {
            CLOG(ERROR, "SDLWindow") << "Could not create SDL_Surface.";
            Stop();
        }
    } else {
        CLOG(ERROR, "SDLWindow") << "Could not create SDL_Window.";
    }
}

void SDLWindow::Stop() {
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void SDLWindow::Swap() {
    if ( screen != NULL ) {
        SDL_UpdateWindowSurface( window );
    }
}

int SDLWindow::GetWidth() {
    return _width;
}

int SDLWindow::GetHeight() {
    return _height;
}
