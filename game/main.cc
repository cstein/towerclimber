#include "base/glwindow.h"
#include "base/controls.h"
#include "base/scenemanager.h"
#include "fonts/fontmanager.h"

#include "renderer/shader.h"
#include "renderer/shadermanager.h"

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

    // attempt to build quads
    std::string quad = "CasperSteinmann!";
    Font* f = fontmanager->Get("Ubuntu Mono");
    LOG(INFO) << "loaded font size: " << f->GetSize();

    float ox, oy;
    float x, y;
    float size;
    x = 50.0f;
    y = 100.0f;
    std::vector<FontVert> vertices;
    for(std::string::iterator it = quad.begin(); it < quad.end(); it++) {
        std::stringstream ss;
        std::string c;
        ss << *it;
        ss >> c;
        CharacterRect* r = f->GetCharRect( c );
        // lets build a quad
        LOG(INFO) << "character '" << *it << "' rect: x=" << r->x << " y=" << r->y << " w=" << r->w << " h=" << r->h << " Ox,y=" << r->oy << ", " << r->ox;
        FontQuad q = FontQuad();

        // 1 quad = 2 triangles = 6 vertices
        //
        // triangles are defined COUNTER-CLOCK wise
        // TL -> BL -> BR
        size = (float)f->GetSize();
        ox = 0.0f * (size -(float)r->ox);
        oy = 0.0f * (size - (float)r->oy);
        vertices.push_back( FontVert() );
        vertices.back().x = x;
        vertices.back().y = y + oy;

        vertices.push_back( FontVert() );
        vertices.back().x = x;
        vertices.back().y = y + (float)r->h + oy;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w;
        vertices.back().y = y + (float)r->h + oy;


        // TL -> BR -> TR
        vertices.push_back( FontVert() );
        vertices.back().x = x;
        vertices.back().y = y +oy;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w;
        vertices.back().y = y + (float)r->h + oy;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w;
        vertices.back().y = y + oy;

        x = x + (float)r->w;
    }

    LOG(INFO) << "size: " << vertices.size();

    GLuint vbo[1];
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( FontVert ), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    f->BindTexture();
    glUseProgram( sm->GetProgram("font-shader" ) );
    Shader* s = sm->Get("font-shader");
    s->SetProjectionMatrix( window->GetProjection() );

    while(running) {
        controls->Update( scenemanager->GetActive() );
        running = !controls->IsExitState();
        //renderer->RenderScene( scenemanager->GetActive() );
        glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        window->Swap();
    }

    glUseProgram( 0 );

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, vbo);

    fontmanager->Stop();
    controls->Stop();
    scenemanager->Stop();
    sm->Stop();
    window->Stop();

}
