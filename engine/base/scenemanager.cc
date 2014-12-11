#include "scenemanager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "jsonxx/jsonxx.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
    _scenes.clear();
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

Scene* SceneManager::GetActiveScene() {
    if (!_scenes.empty())
        return _scenes.back();
    return nullptr;
}

Scene* SceneManager::PopScene() {
    if (_scenes.empty())
        return nullptr;
    Scene* s = _scenes.back();
    _scenes.pop_back();
    return s;
}

void SceneManager::PushScene(Scene* s) {
    _scenes.push_back( s );
}

void SceneManager::Update( double dt ) {
    if (!_scenes.empty()) {
        if (GetActiveScene()->IsDead()) {
            Scene* s = PopScene();
            // here one could do something with the popped Scene
        }
        if (GetActiveScene() != nullptr)
            GetActiveScene()->Update( dt );
    }
}

void SceneManager::Draw() {
    if (!_scenes.empty())
        GetActiveScene()->Draw();
}
