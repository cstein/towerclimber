#ifndef __TEXTNODE_H_
#define __TEXTNODE_H_

#include <string>

#include "fonts/fontmanager.h"
#include "renderer/shadermanager.h"
#include "renderer/rendernode.h"

class TextNode: public RenderNode {
public:
    TextNode(FontManager* fontmanager);
    ~TextNode();
    virtual void Draw();
    void Create(std::string fontname, float scale, float x, float y, std::string text);
    void UpdateText( std::string text );
private:
    std::string _fontname;
    int _textlength;
    Font* _font;
    FontManager* _fontmanager;
    float _scale;

    void SetScale( float scale );
    void SetFontName( std::string fontname );
    void SetText( std::string text );
    void CreateVAOVBO();
    void UpdateVAOVBO();
};

#endif
