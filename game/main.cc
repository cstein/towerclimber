#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"
#include "renderer/textnode.h"


#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

struct FontVert {
    float x;
    float y;
};

struct FontQuad {
    FontVert tl;
    FontVert bl;
    FontVert br;
    FontVert tr;
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

    TextNode tn( fontmanager );
    tn.Create("Ubuntu Light", 1.0f, 200.0, 150.0, "Casper Steinmann ROCKS!");
    tn.Show();
    glUseProgram( sm->GetProgram("font-shader" ) );
    Shader* s = sm->Get("font-shader");
    s->SetProjectionMatrix( window->GetProjection() );

    glEnable(GL_BLEND);
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    while(running) {
        controls->Update( scenemanager->GetActive() );
        running = !controls->IsExitState();
        //renderer->RenderScene( scenemanager->GetActive() );
        glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        tn.Draw();
        window->Swap();
    }

    glUseProgram( 0 );

    fontmanager->Stop();
    controls->Stop();
    scenemanager->Stop();
    sm->Stop();
    window->Stop();

}
