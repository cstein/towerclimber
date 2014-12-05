#ifndef __SCENE_H_
#define __SCENE_H_

#include <vector>

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

    void AddObject(Object o);

    void Update( double dt );
    void Draw();
protected:
    std::vector<Object> _objects;
};

#endif
