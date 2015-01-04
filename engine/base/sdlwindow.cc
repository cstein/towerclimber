#include "sdlwindow.h"

#include "easyloggingpp/src/easylogging++.h"

SDLWindow::SDLWindow() {
    el::Logger* SDLWindowLogger = el::Loggers::getLogger("SDLWindow");
}

SDLWindow::~SDLWindow() {
    //CLOG(INFO, "SDLWindow") << "Bye.";
    el::Loggers::unregisterLogger("SDLWindow");
}

void SDLWindow::Start() {
    Start(640, 480);
}

void SDLWindow::Start(int width, int height) {
    _width = width;
    _height = height;

    //CLOG(INFO, "SDLWindow") << "Creating window. W = " << width << " H = " << height;

    SDL_Init( SDL_INIT_VIDEO );
    window = SDL_CreateWindow( "GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if ( window != nullptr ) {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if ( renderer == nullptr ) {
            CLOG(ERROR, "SDLWindow") << "Could not create SDL_Renderer." << SDL_GetError();
            Stop();
        }
        SDL_RenderSetLogicalSize( renderer, width, height );
    } else {
        CLOG(ERROR, "SDLWindow") << "Could not create SDL_Window: " << SDL_GetError();
    }
}

void SDLWindow::Stop() {
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void SDLWindow::Swap() {
    if ( renderer != NULL ) {
        SDL_SetRenderDrawColor( renderer, 128, 0, 0, 255 );
        SDL_RenderClear( renderer );

        SDL_RenderPresent( renderer );
    }
}

int SDLWindow::GetWidth() {
    return _width;
}

int SDLWindow::GetHeight() {
    return _height;
}
