#include "fontmanager.h"

#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

FontManager::FontManager( SettingsManager* settings, TextureManager* textures ) {
    el::Logger* FontManagerLogger = el::Loggers::getLogger("FontManager");
    el::Logger* FontLogger = el::Loggers::getLogger("Font");

    _settings = settings;
    _textures = textures;
}

FontManager::~FontManager() {
    el::Loggers::unregisterLogger("Font");
    el::Loggers::unregisterLogger("FontManager");
}

void FontManager::Start() {
    if (_settings == nullptr) {
        CLOG(ERROR, "FontManager") << "Invalid SettingManager provided.";
        return;
    }

    if (!_settings->HasSettingsPath("fonts")) {
        CLOG(ERROR, "FontManager") << "Settings for fonts not provided.";
        return;
    }

    SettingsPath* settingspath = _settings->GetSettingsPath("fonts");
    _confpath = settingspath->GetPath();
    _confname = settingspath->GetName();
    std::string conffilename = _confpath + "/" + _confname;

    std::ifstream fontconf;
    std::stringstream buffer;
    std::string fontname;
    jsonxx::Array fonts;
    jsonxx::Object font;

    fontconf.open( conffilename );
    if(fontconf.is_open()) {
        buffer << fontconf.rdbuf();

        if (_configuration.parse( buffer )) {
            fonts = _configuration.get<jsonxx::Array>("fonts");
            CLOG(INFO, "FontManager") <<  "Found " << fonts.size() << " font(s).";

            // now we load the fonts
            for( int i=0; i<fonts.size(); i++) {
                fontname = fonts.get<jsonxx::String>(i);
                if (_configuration.has<jsonxx::Object>( fontname ) ) {
                    CLOG(INFO, "FontManager") << "Loading '" << fontname << "'.";
                    font = _configuration.get<jsonxx::Object>( fontname );
                    int size = font.get<jsonxx::Number>("size");
                    std::string fname = font.get<jsonxx::String>("filename");
                    std::string texname = font.get<jsonxx::String>("texture");
                    _fonts[fontname] = Font( );
                    _fonts[fontname].SetFilename( fname );
                    _fonts[fontname].SetSize( size );
                    _fonts[fontname].SetTexturename( texname );

                    if (_textures->HasTexture( texname )) {
                        Texture* texture = _textures->GetTexture( texname );
                        _fonts[fontname].SetWidth( texture->GetWidth() );
                        _fonts[fontname].SetHeight( texture->GetHeight() );

                        if (!_fonts[fontname].Load()) {
                            CLOG(ERROR, "FontManager") << "Error loading font.";
                            _fonts.erase(fontname);
                        }
                    } else {
                        CLOG(ERROR, "FontManager") << "Could not get texture '" << texname << "'.";
                        _fonts.erase(fontname);
                    }
                } else {
                    CLOG(ERROR, "FontManager") << "Could not find font: '" << fontname << "' in .json file.";
                }
            }
        } else {
             CLOG(ERROR, "FontManager") << "Could not parse '" << conffilename << "'.";
        }
        fontconf.close();
    }
}

void FontManager::Stop() {
}

Font* FontManager::Get(std::string fontname) {
    std::map<std::string, Font>::iterator it = _fonts.find( fontname );
    if (it != _fonts.end()) {
        return &it->second;
    } else {
        CLOG(ERROR, "FontManager") << "Font '" << fontname << "' not found.";
        return nullptr;
    }
}
