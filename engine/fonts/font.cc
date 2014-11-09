#include "font.h"

#include <iostream>
#include <string>
#include <sstream>

#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"
#include "pugixml/src/pugixml.hpp"

Font::Font() {
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

bool Font::LoadTextureAtlas() {
    if ( LoadXML() ) {
        return LoadPNG();
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
            std::stringstream stream;

            stream.str( rect );
            stream >> _charmap[character].x;
            stream >> _charmap[character].y;
            stream >> _charmap[character].w;
            stream >> _charmap[character].h;

            stream.str( offset );
            stream >> _charmap[character].ox;
            stream >> _charmap[character].oy;
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
        CLOG(ERROR, "Font") << "Char '" << character << "' not found.";
        return nullptr;
    }
}
