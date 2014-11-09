#ifndef __SHADER_H_
#define __SHADER_H_

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();
    bool Load(std::string filename);
    void Unload();

    // The shader ID for the program.
    const inline GLuint Get() { return _program; }
private:
    GLuint _program;
    GLuint _vertexshader;
    GLuint _fragmentshader;
    GLuint CreateShader(std::string filename, GLenum type);
    void PrintShaderCompileInfo( GLuint shader_index );
    void PrintProgramLinkInfo( GLuint program_index );
};

#endif
