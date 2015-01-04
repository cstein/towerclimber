#ifndef __SCENE_H_
#define __SCENE_H_

#include <vector>
#include <string>

#include "game/object.h"

/*
 * A scene contains all information about a given state of the system, i.e.
 *
 *   * the game
 *   * the menu
 *   * loading screen
 *
 * but it does not know anything about all the other scenes.
 *
 * Objects are stored in a scene. An object might be:
 *
 *   * A menu
 *   * A level
 *   * The GUI
 *   * Enemies
 *   * Players
 */

class Scene {
public:
    Scene();
    ~Scene();

    virtual void AddObject(Object* o);

    virtual void Update( double dt );
    virtual void Draw();

    virtual std::string GetName();

    /*
     * if a Scene is dead, it should be popped from the stack
     */
    virtual bool IsDead() { return _isdead; }
protected:
    bool _isdead;
    std::string _name;
    std::vector<Object*> _objects;
};

#endif
