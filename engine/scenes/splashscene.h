#ifndef __SPLASHSCENE_H_
#define __SPLASHSCENE_H_

#include <vector>
#include <string>

#include "base/scene.h"
#include "base/texturemanager.h"

#include "game/object.h"

#include "renderer/shadermanager.h"
#include "renderer/splashnode.h"

class SplashScene: public Scene {
public:
    SplashScene(TextureManager* texturemanager, std::string texturename, ShaderManager* shadermanager, std::string shadername, double lifetime);
    ~SplashScene();

    virtual void Update( double dt );
protected:
    ShaderManager* _shadermanager;
    std::string _shadername;
    TextureManager* _texturemanager;
    std::string _texturename;
    Object* splashobject;
    SplashNode* splashnode;

    double _lifetime;
    double _currenttime;
};

#endif
