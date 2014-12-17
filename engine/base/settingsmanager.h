#ifndef __SETTINGSMANAGER_H_
#define __SETTINGSMANAGER_H_

#include <map>
#include <vector>
#include <string>

#include "manager.h"

#define SETTINGSPATH "resources/settings.json"

struct Settings {
};

struct SettingsPath {
    std::string GetName() { return _name; }
    std::string GetPath() { return _path; }
    std::string _name;
    std::string _path;
};

class SettingsManager : public Manager {
public:
    SettingsManager();
    ~SettingsManager();
    virtual void Start();
    virtual void Stop();

    // Getters
    bool HasSettingsPath(std::string name);
    SettingsPath* GetSettingsPath(std::string name);
private:
    bool LoadSettings();

    std::map<std::string, SettingsPath> _settings;
};

#endif
