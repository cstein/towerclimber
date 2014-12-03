#include "renderer/textnode.h"

#include "easyloggingpp/src/easylogging++.h"

TextNode::TextNode(FontManager* fontmanager) {
    _fontmanager = fontmanager;
}

TextNode::~TextNode() {
    if (_fontmanager != nullptr) {
        _fontmanager = nullptr;
    }

    if (_shadermanager != nullptr) {
        _shadermanager = nullptr;
    }
}

void TextNode::Draw() {
    if (!_isvisible)
        return;

    if (!HasShaderAttached())
        return;

    _shadermanager->BindShader( _shadername );

    _font->BindTexture();

    if (_vao != 0) {
        glBindVertexArray( _vao );
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
        glBindVertexArray( 0 );
    }
}

void TextNode::Create(std::string fontname, float scale, float x, float y, std::string text) {

    SetFontName( fontname );
    SetX( x );
    SetY( y );
    SetScale( scale );
    SetText( text );
    CreateVBO();
}

void TextNode::CreateVBO() {
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

void TextNode::SetFontName( std::string fontname ) {
    _fontname = fontname;
    _font = _fontmanager->Get( fontname );
    if (_font == nullptr) {
        return;
    }
}

void TextNode::SetScale( float scale ) {
    _scale = scale;
}

void TextNode::SetText( std::string text ) {

    _text = text;

    float _x = _x0;
    float _y = _y0;


    // generate the quads from the input text string
    for(std::string::iterator it = text.begin(); it < text.end(); it++) {

        // extract each character as an std::string because that is the format that
        // is used in the character loader. It is a bit clunky to say the least.
        std::stringstream ss;
        std::string c;
        // std::noskipws does not seem to work to remove whitespaces in a string
        // so make this lame hack below
        ss <<  *it;
        ss >>  c;
        if (c.length() == 0) {
            c = " ";
        }

        CharacterRect* rect = _font->GetCharRect( c );
        CharacterUV* uvmap = _font->GetCharUV( c );

        // now we generate the quad
        // 1 quad = 2 triangles = 6 vertices
        //
        // triangles are defined COUNTER-CLOCK wise.
        //
        // First triangle is defined in the following way
        // TL -> BL -> BR
        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox);
        _vertices.back().y = _y - _scale*((float)rect->oy);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->u;
        _uvcoordinates.back().y = uvmap->v;

        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox);
        _vertices.back().y = _y - _scale*((float)rect->oy + (float)rect->h);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->u;
        _uvcoordinates.back().y = uvmap->t;

        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox + (float)rect->w);
        _vertices.back().y = _y - _scale*((float)rect->oy + (float)rect->h);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->s;
        _uvcoordinates.back().y = uvmap->t;

        // Second triangle is defined in the following way
        // TL -> BR -> TR
        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox);
        _vertices.back().y = _y - _scale*((float)rect->oy);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->u;
        _uvcoordinates.back().y = uvmap->v;

        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox + (float)rect->w);
        _vertices.back().y = _y - _scale*((float)rect->oy + (float)rect->h);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->s;
        _uvcoordinates.back().y = uvmap->t;

        _vertices.push_back( Vertex2D() );
        _vertices.back().x = _x + _scale*((float)rect->ox + (float)rect->w);
        _vertices.back().y = _y - _scale*((float)rect->oy);

        _uvcoordinates.push_back( Vertex2D() );
        _uvcoordinates.back().x = uvmap->s;
        _uvcoordinates.back().y = uvmap->v;

        _x = _x + _scale*((float)rect->ox + (float)rect->w);
    }
}

void TextNode::UpdateText( std::string text ) {
    if (_text.compare( text ) == 0)
        return;

    _vertices.clear();
    _uvcoordinates.clear();

    int old_length = _text.length();
    SetText( text );

    // see if we can reuse the old VBOs
    if ( old_length == text.length() ) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof( Vertex2D ), &_vertices[0] );

        glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _uvcoordinates.size() * sizeof( Vertex2D ), &_uvcoordinates[0] );
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof( Vertex2D ), &_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, _uvcoordinates.size() * sizeof( Vertex2D ), &_uvcoordinates[0], GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
