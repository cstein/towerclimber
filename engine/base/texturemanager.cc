#include "texturemanager.h"

// 3rd-party includes
#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"

TextureManager::TextureManager( SettingsManager* settings ) {
    _name = "TextureManager";
    _settings = settings;
    _boundtexture = 0;
}

TextureManager::~TextureManager() {
}

void TextureManager::Start() {
    el::Logger* TextureManagerLogger = el::Loggers::getLogger(_name);
    el::Logger* TextureLogger = el::Loggers::getLogger("Texture");

    if (_settings == nullptr) {
        CLOG(ERROR, _name) << "Invalid SettingsManager provided.";
        return;
    }

    if (!_settings->HasSettingsPath("textures")) {
        CLOG(ERROR, _name) << "Settings for textures not provided.";
        return;
    }

    SettingsPath* settingspath = _settings->GetSettingsPath("textures");
    _confpath = settingspath->GetPath();
    _confname = settingspath->GetName();
    std::string conffilename = _confpath + "/" + _confname;

    std::ifstream textureconf;
    std::stringstream buffer;
    std::string texturename;
    jsonxx::Array textures;
    jsonxx::Object texture;

    textureconf.open( conffilename );
    if( textureconf.is_open() ) {
        buffer << textureconf.rdbuf();

        if (_configuration.parse( buffer )) {
            textures = _configuration.get<jsonxx::Array>("textures");
            CLOG(INFO, _name) << "Found " << textures.size() << " texture(s).";

            for(unsigned int i=0; i < textures.size(); i++) {
                texturename = textures.get<jsonxx::String>(i);
                if (_configuration.has<jsonxx::Object>( texturename )) {
                    CLOG(INFO, _name) << "Loading '" << texturename << "'.";
                    texture = _configuration.get<jsonxx::Object>( texturename );

                    std::string filename = texture.get<jsonxx::String>("filename");
                    _textures2[ texturename ] = Texture();
                    _textures2[ texturename ].SetName( texturename );
                    _textures2[ texturename ].SetFilename( _confpath + "/" + filename );

                    // It might not be too wise to load everything here
                    if (!_textures2[ texturename ].Load()) {
                        CLOG(ERROR, _name) << "Error loading font.";
                        _textures2.erase( texturename );
                    }
                } else {
                    CLOG(ERROR, _name) << "Could not find texture: '" << texturename << "' in .json file.";
                }
            }
        } else {
            CLOG(ERROR, _name) << "Could not parse '" << conffilename << "'.";
        }
        textureconf.close();
    }
}

void TextureManager::Stop() {
    el::Loggers::unregisterLogger("Texture");
    el::Loggers::unregisterLogger(_name);
}

bool TextureManager::HasTexture( std::string texturename ) {
    std::map<std::string, Texture>::iterator it = _textures2.find( texturename );
    if (it != _textures2.end()) {
        return true;
    } else {
        return false;
    }

}

bool TextureManager::LoadTexture( std::string texturename ) {
    if (HasTexture( texturename ))
        return true;

    if (LoadPNG( "resources/graphics/" + texturename + ".png" ))
        return CreateTexture( texturename );

    return false;
}

void TextureManager::BindTexture(std::string texturename) {
    if (HasTexture(texturename)) {
        _textures2[ texturename ].Bind();
    }
}

GLuint TextureManager::GetBoundTexture() {
    return _boundtexture;
}

bool TextureManager::LoadPNG( std::string texturename ) {
    CLOG(INFO, _name) << "Loading '" << texturename << "'.";
    _image.clear();
    unsigned int error = lodepng::decode(_image, _imagewidth, _imageheight, texturename.c_str());
    if (error != 0) {
        CLOG(ERROR, _name) << lodepng_error_text(error);
        return false;
    }
    return true;
}

bool TextureManager::CreateTexture( std::string texturename ) {
    _textures[texturename] = 0;
    glGenTextures(1, &_textures[texturename]);
    glBindTexture(GL_TEXTURE_2D, _textures[texturename]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imagewidth, _imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_image[0]);

    // unbind the texture for now
    glBindTexture(GL_TEXTURE_2D, 0);
    return (_textures[texturename] != 0);
}


GLuint TextureManager::GetTextureID( std::string texturename ) {
    std::map<std::string, GLuint>::iterator it = _textures.find( texturename );
    if (it != _textures.end()) {
        return it->second;
    } else {
        return 0;
    }
}

bool TextureManager::UnloadTexture( std::string texturename ) {
    if (HasTexture( texturename )) {
        // if the current texture is bound, unbind it before deletion.
        CLOG(INFO, _name) << "Unloading '" << texturename << "'.";
        if (_boundtexture == _textures[texturename]) {
            _boundtexture = 0;
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        glDeleteTextures(1, &_textures[texturename]);
        _textures.erase(texturename);
        return true;
    }
    return false;
}
