#include <string>
#include <vector>

#include <GL/glew.h>

class Texture {
public:
    Texture();

    /*
     * Getters and Setters for various properties
     */
    void SetName( std::string name ) { _name = name; }
    std::string GetName() { return _name; }

    void SetFilename( std::string filename ) { _filename = filename; }
    std::string GetFilename() { return _filename; }

    GLuint GetID() { return _id; }
    bool HasID() { return _id != 0; }

    // whether or not the texture is bound
    bool IsBound() { return _isbound; }

    // bind or unbind the texture
    void Bind();
    void Unbind();

    void Destroy();
    bool Load();

    unsigned int GetHeight() {return _height;}
    unsigned int GetWidth() {return _width;}
private:
    std::string _name;
    std::string _filename;

    GLuint _id;
    bool _isbound;

    bool LoadPNG();
    unsigned int _width;
    unsigned int _height;
    std::vector<unsigned char> _data;

    // creates and transfers texture to gfx-card
    bool Create();
};
