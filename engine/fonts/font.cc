#include "font.h"

#include <iostream>
#include <string>
#include <sstream>

#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"
#include "pugixml/src/pugixml.hpp"

Font::Font() {
    _textureid = 0;
}

Font::~Font() {
}

void Font::SetSize(unsigned int size) {
    _size = size;
}

void Font::SetFilename(std::string filename) {
    _settingsfilename = "resources/graphics/fonts/" + filename + ".xml";
    _imagefilename = "resources/graphics/fonts/" + filename + ".png";
}

bool Font::Load() {
    if ( LoadXML() ) {
        if ( LoadPNG() ) {
            CreateUVMap();
            return CreateTexture();
        };
    }
    return false;
}
bool Font::LoadXML() {
    CLOG(INFO, "Font") << "Loading '" << _settingsfilename << "'.";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(_settingsfilename.c_str());

    if (result) {
        pugi::xml_node font_node = doc.child("Font");
        for( pugi::xml_node char_node = font_node.child("Char");
                char_node;
                char_node = char_node.next_sibling("Char")) {

            std::string character = char_node.attribute("code").value();
            std::string rect = char_node.attribute("rect").value();
            std::string offset = char_node.attribute("offset").value();

            _charmap[character] = CharacterRect();
            std::stringstream rectstream;

            rectstream.str( rect );
            rectstream >> _charmap[character].x;
            rectstream >> _charmap[character].y;
            rectstream >> _charmap[character].w;
            rectstream >> _charmap[character].h;

            std::stringstream offsetstream;
            offsetstream.str( offset );
            offsetstream >> _charmap[character].ox;
            offsetstream >> _charmap[character].oy;
        }
    } else {
        CLOG(ERROR, "Font") << result.description();
        return false;
    }
    return true;
}

bool Font::LoadPNG() {
    CLOG(INFO, "Font") << "Loading '" << _imagefilename << "'.";
    unsigned int error = lodepng::decode(_image, _imagewidth, _imageheight, _imagefilename.c_str());
    if (error != 0) {
        CLOG(ERROR, "Font") << lodepng_error_text(error);
        return false;
    }
    return true;
}

unsigned int Font::GetSize() {
    return _size;
}

CharacterRect* Font::GetCharRect(std::string character) {
    std::map<std::string, CharacterRect>::iterator it = _charmap.find( character );
    if (it != _charmap.end()) {
        return &it->second;
    } else {
        CLOG(ERROR, "Font") << "Rect for character '" << character << "' not found.";
        return nullptr;
    }
}

bool Font::CreateTexture() {
    glGenTextures(1, &_textureid);
    glBindTexture(GL_TEXTURE_2D, _textureid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imagewidth, _imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_image[0]);
    // unbind the texture for now
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool Font::BindTexture() {
    if (_textureid != 0) {
        glBindTexture(GL_TEXTURE_2D, _textureid);
        return true;
    } else {
        CLOG(ERROR, "Font") << "Could not bind texture.";
        return false;
    }
}

bool Font::UnbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void Font::CreateUVMap() {
    // the Font UV map is actually rather elegant. Each char is defined
    // in a rectangle which is a fraction of the total texture.
    float width = (float)_imagewidth;
    float height = (float)_imageheight;
    float x, y, w, h;
    std::map<std::string, CharacterRect>::iterator it;
    for( it = _charmap.begin(); it != _charmap.end(); it++ ) {
        CharacterRect* cr = &it->second;
        x = (float)cr->x / width;
        y = (float)cr->y / height;
        w = ((float)cr->x + (float)cr->w) / width;
        h = ((float)cr->y + (float)cr->h) / height;
        _uvmap[ it->first ] = CharacterUV();
        _uvmap[ it->first ].u = x;
        _uvmap[ it->first ].v = h;
        _uvmap[ it->first ].s = w;
        _uvmap[ it->first ].t = y;
        //CLOG(INFO, "Font") << "CMAP: '" << it->first << "' " << x << ", " << y << ", " << w << ", " << h;
    }
}

CharacterUV* Font::GetCharUV(std::string character) {
    std::map<std::string, CharacterUV>::iterator it = _uvmap.find( character );
    if (it != _uvmap.end()) {
        return &it->second;
    } else {
        CLOG(ERROR, "Font") << "UV map for character '" << character << "' not found.";
        return nullptr;
    }
}
