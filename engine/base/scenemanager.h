#ifndef __SCENEMANAGER_H_
#define __SCENEMANAGER_H_

#include <vector>

#include "manager.h"
#include "base/scene.h"

/*
 * The SceneManager is responsible for creating all scenes for a game
 *
 *   - loading of the scenes is done when we need them, so the manager does not care about that
 *
 *   * calling Update(dt) will trigger an update on the active scene
 *   * calling Draw() will trigger a draw in the active scene
 */

class SceneManager : public Manager {
public:
    SceneManager();
    ~SceneManager();
    virtual void Start();
    virtual void Stop();

    void PushScene(Scene* s);
    Scene* PopScene();
    Scene* GetActiveScene();

    void Update( double dt );
    void Draw();

protected:
    std::vector<Scene*> _scenes;
};

#endif
