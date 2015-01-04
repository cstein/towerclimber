#include "controls.h"

Controls::Controls() {

}

Controls::~Controls() {

}

void Controls::Start() {
}

void Controls::Stop() {
}

void Controls::Update( Scene* scene ) {
    //if (scene == nullptr) {
    //    return;
    //}
    
    // process all events
    while( SDL_PollEvent( &_event ) ) {
        switch( _event.type ) {
            case SDL_QUIT:
                _isexitstate = true;
                break;
            case SDL_KEYDOWN:
                switch( _event.key.keysym.sym ) {
                    case SDLK_ESCAPE:
                        _isexitstate = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
        }
    }
}

bool Controls::IsExitState() {
    return _isexitstate;
}
