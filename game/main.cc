#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"
#include "renderer/textnode.h"


#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

struct timespec ts;

long get_time_ns() {
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000L + ts.tv_nsec;
}

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
    tn.Create("Liberation Mono", 1.0f, 200.0, 150.0, "Casper Steinmann ROCKS!");
    tn.Show();
    glUseProgram( sm->GetProgram("font-shader" ) );
    Shader* s = sm->Get("font-shader");
    s->SetProjectionMatrix( window->GetProjection() );

    long total_time = 0L;
    long delta_time = 1000000L;
    
    long current_time = get_time_ns();
    long accumulator = 0L;

    glEnable(GL_BLEND);
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    while(running) {
        long new_time = get_time_ns();
        long frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        while( accumulator >= delta_time ) {
            // integrate physics here using t and dt
            controls->Update( scenemanager->GetActive() );
            running = !controls->IsExitState();
            accumulator -= delta_time;
            total_time += delta_time;
        }

        //renderer->RenderScene( scenemanager->GetActive() );
        glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        tn.Draw();
        window->Swap();

        std::cout << "frame time: " << frame_time << " total time: " << total_time << " current time: " << current_time << " accumulator: " << accumulator << std::endl;
        //if (t > 10000000000L)
        //    break;
    }

    glUseProgram( 0 );

    fontmanager->Stop();
    controls->Stop();
    scenemanager->Stop();
    sm->Stop();
    window->Stop();

}
