#ifndef __FONTMANAGER_H_
#define __FONTMANAGER_H_

#include "base/manager.h"
#include "fonts/font.h"

#include <string>
#include <map>

#include "jsonxx/jsonxx.h"
#include "pugixml/src/pugixml.hpp"

class FontManager: public Manager {
public:
    FontManager(std::string path, std::string name);
    ~FontManager();
    virtual void Start();
    virtual void Stop();
    Font* Get( std::string fontname );

    unsigned int GetNumFonts() { return _fonts.size(); }
private:
    std::string _confpath;
    std::string _confname;
    jsonxx::Object _configuration;
    std::map<std::string, Font> _fonts;
};

#endif
