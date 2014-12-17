#include "base/settingsmanager.h"

#include <fstream>

#include "jsonxx/jsonxx.h"
#include "easyloggingpp/src/easylogging++.h"

SettingsManager::SettingsManager() {
    el::Logger* SettingsManagerLogger = el::Loggers::getLogger("SettingsManager");
}

SettingsManager::~SettingsManager() {
    el::Loggers::unregisterLogger("SettingsManager");
}

void SettingsManager::Start() {
    if (!LoadSettings()) {
        CLOG(ERROR, "SettingsManager") << "Could not load '" << SETTINGSPATH << "'.";
    }
}

void SettingsManager::Stop() {

}

bool SettingsManager::LoadSettings() {
    std::ifstream configurationfile;
    std::stringstream buffer;
    jsonxx::Object configuration;
    configurationfile.open( SETTINGSPATH );
    if( configurationfile.is_open() ) {
        buffer << configurationfile.rdbuf();
        if (configuration.parse( buffer )) {

            if (!configuration.has<jsonxx::Array>( "settings" )) {
                CLOG(ERROR, "SettingsManager") << "JSON array 'settings' missing from '" << SETTINGSPATH << "'.";
                return false;
            }

            // now actually load the array of groups we need and parse each one
            jsonxx::Array paths = configuration.get<jsonxx::Array>( "settings" );
            for (unsigned char i=0; i < paths.size(); i++) {
                std::string pathname = paths.get<jsonxx::String>(i);

                if (configuration.has<jsonxx::Object>( pathname )) {
                    _settings[pathname] = SettingsPath();
                    jsonxx::Object path = configuration.get<jsonxx::Object>( pathname );

                    if (path.has<jsonxx::String>("path") && path.has<jsonxx::String>("name")) {
                        _settings[pathname]._name = path.get<jsonxx::String>("name");
                        _settings[pathname]._path = path.get<jsonxx::String>("path");
                    } else {
                        CLOG(ERROR, "SettingsManager") << "Item '" << pathname << "' misses 'name' and/or 'path'.";
                        _settings.erase( pathname );
                    }
                } else {
                    CLOG(ERROR, "SettingsManager") << "Could not load path '" << pathname << "'.";
                }
            }
            return true;

        } else {
            CLOG(ERROR, "SettingsManager") << "Could not parse '" << SETTINGSPATH << "'.";
        }
        configurationfile.close();
    }
    return false;
}

bool SettingsManager::HasSettingsPath( std::string name ) {
    std::map<std::string, SettingsPath>::iterator it = _settings.find( name );
    if (it != _settings.end()) {
        return true;
    }
    return false;
}
