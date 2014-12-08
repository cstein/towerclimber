#ifndef __SPLASHNODE_H_
#define __SPLASHNODE_H_

#include <string>

#include "renderer/shadermanager.h"
#include "renderer/rendernode.h"

class SplashNode: public RenderNode {
public:
    SplashNode();
    ~SplashNode();
    void Create(std::string texturename);
private:
    std::string _texturename;
    void CreateVBO();

    virtual void OnDraw();
};

#endif
