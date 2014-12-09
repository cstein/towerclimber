#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include <vector>
#include <map>

#include <GL/glew.h>

#include "manager.h"

/*
 * The TextureManager is loading and binding textures.
 */

class TextureManager : public Manager {
public:
    TextureManager();
    ~TextureManager();
    virtual void Start();
    virtual void Stop();
    bool HasTexture( std::string texturename );
    bool LoadTexture( std::string texturename );
    void BindTexture( std::string texturename );
    GLuint GetBoundTexture();
private:
    GLuint _boundtexture;
    std::map<std::string, GLuint> _textures;

    unsigned int _imagewidth;
    unsigned int _imageheight;
    std::vector<unsigned char> _image;
    bool LoadPNG( std::string texturename );
    bool CreateTexture( std::string texturename );
    GLuint GetTextureID( std::string texturename );
};

#endif
