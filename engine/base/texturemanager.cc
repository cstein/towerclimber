#include "texturemanager.h"

// 3rd-party includes
#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"

TextureManager::TextureManager( SettingsManager* settings ) {
    _name = "TextureManager";
    _settings = settings;
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

void TextureManager::BindTexture(std::string texturename) {
    if (HasTexture(texturename)) {
        _textures2[ texturename ].Bind();
    }
}

Texture* TextureManager::GetTexture( std::string texturename ) {
    std::map<std::string, Texture>::iterator it = _textures2.find( texturename );
    if (it != _textures2.end()) {
        return &it->second;
    } else {
        return nullptr;
    }
}
