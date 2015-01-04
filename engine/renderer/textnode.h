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
    void Create(std::string fontname, float scale, float x, float y, std::string text);
    void UpdateText( std::string text );
private:
    std::string _fontname;
    std::string _text;
    Font* _font;
    FontManager* _fontmanager;
    float _scale;

    void SetScale( float scale );
    void SetFontName( std::string fontname );
    void SetText( std::string text );
    void CreateVBO();

    virtual void OnDraw();
};

#endif
