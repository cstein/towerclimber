#ifndef __SHADERMANAGER_H_
#define __SHADERMANAGER_H_

#include "base/manager.h"
#include "renderer/shader.h"

#include <string>
#include <map>

#include "jsonxx/jsonxx.h"
#include "pugixml/src/pugixml.hpp"
#include <Eigen/Core>

class ShaderManager: public Manager {
public:
    ShaderManager();
    ~ShaderManager();
    virtual void Start();
    virtual void Stop();

    bool HasShader( std::string shadername );
    Shader* GetShader( std::string shadername );
    const inline GLuint GetBoundShaderID() { return _currentshaderid; }
    Shader* GetBoundShader() { return _currentshader; }
    bool BindShader( std::string shadername );

    /*
     * Uniform variable updates
     */
    void SetProjectionMatrix( Eigen::Matrix4f P );
private:
    GLuint _currentshaderid;
    Shader* _currentshader;
    jsonxx::Object _configuration;
    std::map<std::string, Shader> _shaders;

    Eigen::Matrix4f _uniform_projection_matrix;
};

#endif
