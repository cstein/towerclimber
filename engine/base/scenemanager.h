#ifndef __SCENEMANAGER_H_
#define __SCENEMANAGER_H_

#include <vector>

#include "manager.h"
#include "scene.h"

/*
 * The SceneManager is responsible for creating all scenes for a game
 *
 *   - loading of the scenes is done when we need them, so the manager does not care about that
 */

class SceneManager : public Manager {
public:
    SceneManager();
    ~SceneManager();
    virtual void Start();
    virtual void Stop();

    void AddScene(Scene* s);
    Scene* PopScene();
    Scene* GetActiveScene();

    void Update();

protected:
    std::vector<Scene*> _scenes;

};

#endif
