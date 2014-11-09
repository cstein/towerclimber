#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"

#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

struct FontVert {
    float _x;
    float _y;
    FontVert():
        _x(0.0f),
        _y(0.0f) {
    }
    FontVert(float x, float y) {
        _x = x;
        _y = y;
    }
    void print() {
        LOG(INFO) << "VERTEX: x, y = " << _x << " " << _y;
    }
};

struct FontQuad {
    FontVert tl;
    FontVert bl;
    FontVert br;
    FontVert tr;

    void print() {
        tl.print();
        bl.print();
        br.print();
        tr.print();
    }
};

int main() {
    bool running = true;

    GLWindow* window = new GLWindow();
    window->Start(800, 600);

    ShaderManager* sm = new ShaderManager();
    sm->Start();


    // start engine subsystems
    // SceneManager manages all scenes (aka game screens, i.e. menus, levels etc)
    SceneManager* scenemanager = new SceneManager();
    scenemanager->Start();

    Controls* controls = new Controls();
    controls->Start();

    FontManager* fontmanager = new FontManager();
    fontmanager->Start();

    // attempt to build quads
    std::string quad = "Casper!";
    Font* f = fontmanager->Get("Ubuntu Mono");
    LOG(INFO) << "loaded font size: " << f->GetSize();

    float x, y;
    x = 0.0f;
    y = 0.0f;
    for(std::string::iterator it = quad.begin(); it < quad.end(); it++) {
        std::stringstream ss;
        std::string c;
        ss << *it;
        ss >> c;
        CharacterRect* r = f->GetCharRect( c );
        // lets build a quad
        LOG(INFO) << "character '" << *it << "' rect: x=" << r->x << " y=" << r->y << " w=" << r->w << " h=" << r->h << " Qx=" << x;
        FontQuad q = FontQuad();
        q.tl = FontVert( x, y );
        q.bl = FontVert( x, y + (float)r->h );
        q.br = FontVert( x + (float)r->w, y + (float)r->h );
        q.tr = FontVert( x + (float)r->w, y );
        q.print();
        x = x + (float)r->w;
    }

    while(running) {
        controls->Update( scenemanager->GetActive() );
        running = !controls->IsExitState();
        //renderer->RenderScene( scenemanager->GetActive() );
        window->Swap();
    }

    fontmanager->Stop();
    controls->Stop();
    scenemanager->Stop();
    sm->Stop();
    window->Stop();

}
