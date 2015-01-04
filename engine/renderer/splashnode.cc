#include "renderer/splashnode.h"

#include "easyloggingpp/src/easylogging++.h"

SplashNode::SplashNode()
    : RenderNode()
{
}

SplashNode::~SplashNode() {
    if (_shadermanager != nullptr) {
        _shadermanager = nullptr;
    }
}

void SplashNode::OnDraw() {
    if (!_isvisible)
        return;

    if (!HasShaderAttached())
        return;

    _shadermanager->BindShader( _shadername );
    _texturemanager->BindTexture( _texturename );

    if (_vao != 0) {
        glBindVertexArray( _vao );
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
        glBindVertexArray( 0 );
    }
}

void SplashNode::CreateVBO() {
    if (_vao == 0) {
        if (CreateVAO()) {
            glBindVertexArray( _vao );
            glGenBuffers(2, _vbo);

            glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof( Vertex2D ), &_vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
            glBufferData(GL_ARRAY_BUFFER, _uvcoordinates.size() * sizeof( Vertex2D ), &_uvcoordinates[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            // unbind the VBO and VAO so they are not altered later.
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray( 0 );
        }
    }

}

void SplashNode::Create(std::string texturename) {

    _texturename = texturename;

    // now we generate the quad
    // 1 quad = 2 triangles = 6 vertices
    //
    // triangles are defined COUNTER-CLOCK wise.
    //
    // First triangle is defined in the following way
    // TL -> BL -> BR
    float x = 200.0;
    float y = 100.0;
    float w = 400.0;
    float h = 400.0;

    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x;
    _vertices.back().y = y + h;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 0.0f;
    _uvcoordinates.back().y = 0.0f;

    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x;
    _vertices.back().y = y;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 0.0f;
    _uvcoordinates.back().y = 1.0f;

    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x + w;
    _vertices.back().y = y;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 1.0f;
    _uvcoordinates.back().y = 1.0f;


    // Second triangle is defined in the following way
    // TL -> BR -> TR
    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x;
    _vertices.back().y = y + h;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 0.0f;
    _uvcoordinates.back().y = 0.0f;

    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x + w;
    _vertices.back().y = y;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 1.0f;
    _uvcoordinates.back().y = 1.0f;

    _vertices.push_back( Vertex2D() );
    _vertices.back().x = x + w;
    _vertices.back().y = y + h;

    _uvcoordinates.push_back( Vertex2D() );
    _uvcoordinates.back().x = 1.0f;
    _uvcoordinates.back().y = 0.0f;


    CreateVBO();
}
