#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "base/settingsmanager.h"

#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"
#include "renderer/splashnode.h"
#include "renderer/textnode.h"

#include "scenes/splashscene.h"

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

    SettingsManager* settings = new SettingsManager();
    settings->Start();

    GLWindow* window = new GLWindow();
    window->Start(800, 600);

    ShaderManager* sm = new ShaderManager( settings );
    sm->Start();

    Controls* controls = new Controls();
    controls->Start();

    FontManager* fontmanager = new FontManager( settings );
    fontmanager->Start();

    // start engine subsystems
    // SceneManager manages all scenes (aka game screens, i.e. menus, levels etc)
    SceneManager* scenemanager = new SceneManager();
    scenemanager->Start();

    TextureManager* texturemanager = new TextureManager( settings );
    texturemanager->Start();
    //texturemanager->LoadTexture("welogo");
    //texturemanager->LoadTexture("testtexture");

    //SplashScene* s2 = new SplashScene(texturemanager, "testtexture", sm, "splash-shader", 5000.0f);
    //scenemanager->PushScene( s2 );

    SplashScene* ss = new SplashScene(texturemanager, "SPLASH_WELOGO_01", sm, "splash-shader", 5000.0f);
    scenemanager->PushScene( ss );


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
            scenemanager->Update(16.667f);
            running = !controls->IsExitState();
            accumulator -= delta_time;
            total_time += delta_time;
        }

        //glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);

        sm->SetProjectionMatrix( window->GetProjection() );

        scenemanager->Draw();

        tn.Draw();
        tt.Draw();

        window->Swap();
    }

    glUseProgram( 0 );

    texturemanager->Stop();
    scenemanager->Stop();
    fontmanager->Stop();
    controls->Stop();
    sm->Stop();
    window->Stop();
    settings->Stop();
}
