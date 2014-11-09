#ifndef __SHADERMANAGER_H_
#define __SHADERMANAGER_H_

#include "base/manager.h"
#include "renderer/shader.h"

#include <string>
#include <map>

#include "jsonxx/jsonxx.h"
#include "pugixml/src/pugixml.hpp"

class ShaderManager: public Manager {
public:
    ShaderManager();
    ~ShaderManager();
    virtual void Start();
    virtual void Stop();
    GLuint GetProgram( std::string shadername ) { return _shaders[ shadername ].Get(); }
    Shader* Get( std::string shadername ) { return &_shaders[ shadername ]; }
private:
    GLuint _currentshader;
    jsonxx::Object _configuration;
    std::map<std::string, Shader> _shaders;
};

#endif
