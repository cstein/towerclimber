#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include <vector>
#include <map>

#include <GL/glew.h>

#include "base/manager.h"
#include "base/settingsmanager.h"
#include "renderer/texture.h"

#include "jsonxx/jsonxx.h"

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
    void BindTexture( std::string texturename );
    unsigned int GetNumLoadedTextures() { return _textures2.size(); }

    Texture* GetTexture( std::string texturename );
private:
    SettingsManager* _settings;
    jsonxx::Object _configuration;
    std::map<std::string, Texture> _textures2;
};

#endif
