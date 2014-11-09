#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"

#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

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
