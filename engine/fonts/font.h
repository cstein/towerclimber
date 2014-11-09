#ifndef __FONT_H_
#define __FONT_H_

#include <map>
#include <string>
#include <vector>

struct CharacterRect {
    int x;
    int y;
    int w;
    int h;
    int ox; // offsets
    int oy;
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

    // Loads the XML and PNG data into the font.
    bool LoadTextureAtlas();

    CharacterRect* GetCharRect(std::string character);
    unsigned int GetSize();
private:
    std::string _settingsfilename;
    std::string _imagefilename;

    // size of the font
    unsigned int _size;

    // contains the character map, i.e. uv mapping in texture coordinates
    std::map<std::string, CharacterRect> _charmap;

    unsigned int _imagewidth;
    unsigned int _imageheight;
    std::vector<unsigned char> _image;


    // Loads the font .xml configuration file with character rectangles.
    bool LoadXML();

    // Loads the PNG image
    bool LoadPNG();
};

#endif
