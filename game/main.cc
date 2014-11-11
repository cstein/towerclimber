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
    std::string quad("Welcome to my world.");
    //Font* f = fontmanager->Get("Ubuntu Mono");
    Font* f = fontmanager->Get("Liberation Mono");
    LOG(INFO) << "loaded font size: " << f->GetSize();

    float ox, oy;
    float x, y;
    float size;
    x = 100.0f;
    y = 100.0f;
    std::vector<FontVert> vertices;
    std::vector<FontVert> uvs;
    for(std::string::iterator it = quad.begin(); it < quad.end(); it++) {
        std::stringstream ss;
        std::string c;
        // std::noskipws does not seem to work, make this lame hack below
        ss <<  *it;
        ss >>  c;
        if (c.length() == 0) {
            c = " ";
        }

        // extract character information needed
        CharacterRect* r = f->GetCharRect( c );
        CharacterUV* u = f->GetCharUV( c );
        // lets build a quad
        FontQuad q = FontQuad();

        // 1 quad = 2 triangles = 6 vertices
        //
        // each vertex also holds a UV coordinate
        //
        // triangles are defined COUNTER-CLOCK wise
        // TL -> BL -> BR
        size = (float)f->GetSize();
        ox =  (float)r->ox;
        oy = -(float)r->oy; //0.0f; //size - (float)r->h + (float)r->oy;
        vertices.push_back( FontVert() );
        vertices.back().x = x + ox;
        vertices.back().y = y + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->u;
        uvs.back().y = u->v;

        vertices.push_back( FontVert() );
        vertices.back().x = x + ox;
        vertices.back().y = y - (float)r->h + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->u;
        uvs.back().y = u->t;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w + ox;
        vertices.back().y = y - (float)r->h + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->s;
        uvs.back().y = u->t;

        // TL -> BR -> TR
        vertices.push_back( FontVert() );
        vertices.back().x = x + ox;
        vertices.back().y = y + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->u;
        uvs.back().y = u->v;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w + ox;
        vertices.back().y = y - (float)r->h + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->s;
        uvs.back().y = u->t;

        vertices.push_back( FontVert() );
        vertices.back().x = x + (float)r->w + ox;
        vertices.back().y = y + oy;

        uvs.push_back( FontVert() );
        uvs.back().x = u->s;
        uvs.back().y = u->v;

        x = x + (float)r->w + ox;
    }

    LOG(INFO) << "size: " << vertices.size();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo[2];
    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( FontVert ), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof( FontVert ), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);

    f->BindTexture();
    glUseProgram( sm->GetProgram("font-shader" ) );
    Shader* s = sm->Get("font-shader");
    s->SetProjectionMatrix( window->GetProjection() );

    glBindVertexArray( vao );
    glEnable(GL_BLEND);
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    while(running) {
        controls->Update( scenemanager->GetActive() );
        running = !controls->IsExitState();
        //renderer->RenderScene( scenemanager->GetActive() );
        glClearColor( 0.39, 0.58, 0.93, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        window->Swap();
    }

    glBindVertexArray( 0 );
    glUseProgram( 0 );

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glDeleteBuffers(2, vbo);

    fontmanager->Stop();
    controls->Stop();
    scenemanager->Stop();
    sm->Stop();
    window->Stop();

}
