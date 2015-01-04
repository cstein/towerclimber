#ifndef __FONT_H_
#define __FONT_H_

#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>

struct CharacterRect {
    int x;
    int y;
    int w;
    int h;
    int ox; // offsets
    int oy;
};

struct CharacterUV {
    float u;
    float v;
    float s;
    float t;
};

/*
 * The Font class holds information for a font, such as size,
 * weight, texture atlas and UV coordinates for each character
 */
class Font {
public:
    Font();
    ~Font();
    void SetSize(unsigned int value);
    void SetFilename(std::string filename);
    void SetTexturename(std::string texturename);
    std::string GetTextureName() { return _texturename; }
    void SetHeight( unsigned int value ) { _imageheight = value; }
    void SetWidth( unsigned int value ) { _imagewidth = value; }

    // Loads the XML and PNG data into the font.
    bool Load();

    CharacterRect* GetCharRect(std::string character);
    CharacterUV* GetCharUV(std::string character);
    unsigned int GetSize();
private:
    std::string _settingsfilename;
    std::string _imagefilename;
    std::string _texturename;

    // size of the font
    unsigned int _size;

    // contains the character map, i.e. uv mapping in texture coordinates
    std::map<std::string, CharacterRect> _charmap;
    std::map<std::string, CharacterUV> _uvmap;

    unsigned int _imagewidth;
    unsigned int _imageheight;

    // Loads the font .xml configuration file with character rectangles.
    bool LoadXML();
    //
    // Creates the UV map
    void CreateUVMap();
};

#endif
