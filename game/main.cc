#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"
#include "renderer/textnode.h"

#include "game/object.h"

#include <stdio.h>


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

    Controls* controls = new Controls();
    controls->Start();

    FontManager* fontmanager = new FontManager();
    fontmanager->Start();

    // start engine subsystems
    // SceneManager manages all scenes (aka game screens, i.e. menus, levels etc)
    SceneManager* scenemanager = new SceneManager();
    scenemanager->Start();


    Scene* s1 = new Scene();
    scenemanager->PushScene( s1 );

    Object* o1 = new Object();
    s1->AddObject(o1);

    TextNode* test1 = new TextNode( fontmanager );
    test1->Create("Ubuntu Mono", 1.0f, 100.0, 200.0, "SceneManager");
    test1->AttachShader( sm, "font-shader" );
    test1->Show();
    o1->AddNode( test1 );

    Object* o2 = new Object();
    s1->AddObject(o2);

    TextNode* test2 = new TextNode( fontmanager );
    test2->Create("Ubuntu Mono", 1.0f, 100.0, 300.0, "Label 2");
    test2->AttachShader( sm, "font-shader" );
    test2->Show();
    o2->AddNode( test2 );


    TextNode tn( fontmanager );
    tn.Create("Ubuntu Mono", 1.0f, 20.0, 580.0, "Frame time:");
    tn.AttachShader( sm, "font-shader" );
    tn.Show();
    TextNode tt( fontmanager );
    tt.Create("Ubuntu Light", 1.0f, 20.0f, 20.0f, "Testing Casper Steinmann Testing -");
    tt.AttachShader( sm, "font-shader" );
    tt.Show();

    long total_time = 0L;
    long delta_time = 16667000L;
    long current_time = get_time_ns();
    long accumulator = 0L;

    long frame_time_average = 0L;
    int frame_count = 0;
    long last_time = current_time;

    glEnable(GL_BLEND);
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    while(running) {
        long new_time = get_time_ns();
        long frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        // frame counter start
        frame_time_average += frame_time;
        frame_count += 1;
        if (current_time - last_time > 1000000000L) {
            double fta = (double)frame_time_average / (1000000.0 * (double)frame_count);
            char string [18];
            sprintf( string, "Frame time: %6.3f", fta );
            frame_count = 0;
            last_time += 1000000000L;
            frame_time_average = 0;

            std::string ss( string );
            tn.UpdateText( ss );
        }
        // frame counter end

        while( accumulator >= delta_time ) {
            // integrate physics here using t and dt
            controls->Update( scenemanager->GetActiveScene() );
            scenemanager->Update(0.016);
            running = !controls->IsExitState();
            accumulator -= delta_time;
            total_time += delta_time;
        }

        if( total_time > 3000000000L ) {
            o1->SetDrawable( true );
            o2->SetDrawable( true );
        }

        //renderer->RenderScene( scenemanager->GetActive() );
        glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        tn.Draw();
        tt.Draw();
        scenemanager->Draw();

        sm->GetBoundShader()->SetProjectionMatrix( window->GetProjection() );

        window->Swap();
    }

    glUseProgram( 0 );

    scenemanager->Stop();
    fontmanager->Stop();
    controls->Stop();
    sm->Stop();
    window->Stop();

}
