#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include <vector>
#include <map>

#include <GL/glew.h>

#include "manager.h"
#include "base/settingsmanager.h"

/*
 * The TextureManager is loading and binding textures.
 */

class TextureManager : public Manager {
public:
    TextureManager( SettingsManager* settings );
    ~TextureManager();
    virtual void Start();
    virtual void Stop();
    bool HasTexture( std::string texturename );
    bool LoadTexture( std::string texturename );
    void BindTexture( std::string texturename );
    bool UnloadTexture( std::string texturename );
    GLuint GetBoundTexture();
    unsigned int GetNumLoadedTextures() { return _textures.size(); }
private:
    SettingsManager* _settings;

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
