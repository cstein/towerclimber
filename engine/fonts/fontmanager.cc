#include "fontmanager.h"

#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

FontManager::FontManager() {
    el::Logger* FontManagerLogger = el::Loggers::getLogger("FontManager");
    el::Logger* FontLogger = el::Loggers::getLogger("Font");
}

FontManager::~FontManager() {
    el::Loggers::unregisterLogger("Font");
    el::Loggers::unregisterLogger("FontManager");
}

void FontManager::Start() {
    std::ifstream fontconf;
    std::stringstream buffer;
    std::string fontname;
    jsonxx::Array fonts;
    jsonxx::Object font;
    fontconf.open("resources/graphics/fonts/fonts.json");
    if(fontconf.is_open()) {
        buffer << fontconf.rdbuf();
        if (_configuration.parse( buffer )) {
            CLOG(INFO, "FontManager") << "Configuration loaded.";
            fonts = _configuration.get<jsonxx::Array>("fonts");
            CLOG(INFO, "FontManager") <<  "Found " << fonts.size() << " fonts.";

            // now we load the fonts
            for( int i=0; i<fonts.size(); i++) {
                fontname = fonts.get<jsonxx::String>(i);
                if (_configuration.has<jsonxx::Object>( fontname ) ) {
                    CLOG(INFO, "FontManager") << "Loading '" << fontname << "'.";
                    font = _configuration.get<jsonxx::Object>( fontname );
                    int size = font.get<jsonxx::Number>("size");
                    std::string fname = font.get<jsonxx::String>("filename");
                    _fonts[fontname] = Font( );
                    _fonts[fontname].SetFilename( fname );
                    _fonts[fontname].SetSize( size );
                    if (!_fonts[fontname].LoadTextureAtlas()) {
                        CLOG(ERROR, "FontManager") << "Error loading font.";
                        _fonts.erase(fontname);
                    }
                } else {
                    CLOG(ERROR, "FontManager") << "Could not find font: '" << fontname << "' in .json file.";
                }
            }
        } else {
             CLOG(ERROR, "FontManager") << "Could not parse .json file." << std::endl;
        }
    }

    fontconf.close();
}

void FontManager::Stop() {
}
