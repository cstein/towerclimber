#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <vector>

#include "base/node.h"

// forward declaration
class Scene;

/*
 * The most basic of objects that can exist in a game. All things that will interact
 * in the game are descendants of objects (aka gameobjects)
 *
 * Has methods to add nodes (renderable representation, physics, transform, etc.)
 *
 */

class Object {
public:
    Object();
    ~Object();
    virtual void SetParentScene(Scene* parentscene);
    virtual void AddNode(Node* node);

    virtual void Update( double dt );
    virtual void Draw();

    void SetDrawable( bool value );
protected:
    bool _isdrawable;
    Scene* _parentscene;
    std::vector<Node*> _nodes;
};

#endif
