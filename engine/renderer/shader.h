#ifndef __SHADER_H_
#define __SHADER_H_

#include <GL/glew.h>
#include <string>

#include <Eigen/Core>

class Shader {
public:
    Shader();
    ~Shader();
    bool Load();
    void Unload();

    void SetShaderName( std::string name );
    void SetVertexShaderFilename( std::string filename );
    void SetFragmentShaderFilename( std::string filename );

    // The shader ID for the program.
    const inline GLuint Get() { return _program; }

    // Uniforms
    void SetProjectionMatrix( Eigen::Matrix4f P );
private:
    std::string _name;
    std::string _basepath;
    std::string _vertexshaderfilename;
    std::string _fragmentshaderfilename;

    GLuint _program;
    GLuint _vertexshader;
    GLuint _fragmentshader;
    GLuint CreateShader(std::string filename, GLenum type);
    void PrintShaderCompileInfo( GLuint shader_index );
    void PrintProgramLinkInfo( GLuint program_index );

    void SetupShaderLocations();
    // variables for vertexattribs
    GLuint _position;
    GLuint _texcoords;

    // variables for uniforms
    GLuint _uniformprojectionmatrix;
};

#endif