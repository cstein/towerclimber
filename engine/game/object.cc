#include "object.h"

Object::Object() {
    _parentscene = nullptr;
    _isdrawable = false;
}

Object::~Object() {
    if (_parentscene != nullptr)
        _parentscene = nullptr;

    _nodes.clear();
}

void Object::SetParentScene(Scene* parentscene) {
    if (parentscene != nullptr) {
        _parentscene = parentscene;
    }
}

void Object::AddNode(Node* node) {
    _nodes.push_back( node );
}

void Object::Update( double dt ) {
    if (!_nodes.empty()) {
        for(std::vector<Node*>::iterator it = _nodes.begin();
            it != _nodes.end();
            it ++) {

            (*it)->Update( dt );
        }
    }
}

void Object::Draw() {
    if (!_isdrawable)
        return;

    if (!_nodes.empty()) {
        for(std::vector<Node*>::iterator it = _nodes.begin();
            it != _nodes.end();
            it ++) {

            (*it)->Draw();
        }
    }
}

void Object::SetDrawable( bool value ) {
    _isdrawable = value;
}
