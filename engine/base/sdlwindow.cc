#include "sdlwindow.h"

#include <iostream>

SDLWindow::SDLWindow() {

}

void SDLWindow::Start() {
    Start(640, 480);
}

void SDLWindow::Start(int width, int height) {
    _width = width;
    _height = height;

    SDL_Init( SDL_INIT_VIDEO );
    window = SDL_CreateWindow( "GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if ( window != NULL ) {
        screen = SDL_GetWindowSurface( window );
        if ( screen == NULL ) {
            std::cout << "ERROR" << std::endl;
            Stop();
        }
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
