#include "scenemanager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "jsonxx/jsonxx.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}

Scene* SceneManager::GetActive() {
    return nullptr;
}

// this will initiate all scenes (but not load them)
void SceneManager::Start() {
    std::string line;
    std::ifstream t;
    std::stringstream buffer;
    t.open("scenemanager.json");
    if (t.is_open()) {
        buffer << t.rdbuf();
        jsonxx::Object o;
        o.parse( buffer );
        std::cout << o.has<jsonxx::Object>("scene") << std::endl;
        std::cout << o.json() << std::endl;
    }
}

void SceneManager::Stop() {

}
