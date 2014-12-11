#include "scene.h"

Scene::Scene() {
    _isdead = false;
}

Scene::~Scene() {
    _objects.clear();
}

void Scene::AddObject(Object* o) {
    _objects.push_back(o);
}

void Scene::Update( double dt ) {
    if (!_objects.empty()) {
        for(std::vector<Object*>::iterator it = _objects.begin();
            it != _objects.end();
            it ++) {

            (*it)->Update( dt );
        }
    }
}

void Scene::Draw() {
    if (!_objects.empty()) {
        for(std::vector<Object*>::iterator it = _objects.begin();
            it != _objects.end();
            it ++) {

            (*it)->Draw();
        }
    }
}

std::string Scene::GetName() {
    return _name;
}
