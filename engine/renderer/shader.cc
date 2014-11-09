#include "shader.h"

#include <sstream>
#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

Shader::Shader() {
}

Shader::~Shader() {
}

bool Shader::Load(std::string filename) {
    std::string vertexfilename = filename + ".vert";
    std::string fragmentfilename = filename + ".frag";

    int params;

    _program = glCreateProgram();
    if ( _program != 0 ) {
        _vertexshader = CreateShader(vertexfilename, GL_VERTEX_SHADER);
        if ( _vertexshader != 0 ) {
            _fragmentshader = CreateShader(fragmentfilename, GL_FRAGMENT_SHADER);
            if ( _fragmentshader != 0 ) {
                glAttachShader( _program, _vertexshader );
                glAttachShader( _program, _fragmentshader );
                glLinkProgram( _program );
                params = -1;
                glGetProgramiv( _program, GL_LINK_STATUS, &params );
                if ( params != GL_TRUE ) {
                    PrintProgramLinkInfo( _program );
                    LOG(ERROR) << "Could not link program. Filename = " << filename;
                    Unload();
                    return false;
                }
            } else {
                LOG(ERROR) << "Could not fix fragment shader." << filename;
                Unload();
                return false;
            }
        } else {
            LOG(ERROR) << "Could not fix vertex shader." << filename;
            Unload();
            return false;
        }
    }
    return true;
}

void Shader::Unload() {
    if ( _program == 0 )
        return;

    if ( _fragmentshader != 0 ) {
        glDetachShader( _program, _fragmentshader );
        glDeleteShader( _fragmentshader );
        _fragmentshader = 0;
    }

    if ( _vertexshader != 0 ) {
        glDetachShader( _program, _vertexshader );
        glDeleteShader( _vertexshader );
        _vertexshader = 0;
    }

    glDeleteProgram( _program );
    _program = 0;
}

GLuint Shader::CreateShader(std::string filename, GLenum shaderType) {
    GLuint _shader;
    int params;
    std::ifstream shaderfile;
    std::stringstream buffer;
    shaderfile.open(filename);

    _shader = glCreateShader( shaderType );
    if ( shaderfile.is_open() ) {
        buffer << shaderfile.rdbuf();
        std::string s = buffer.str();
        const char* p = s.c_str();
        glShaderSource( _shader, 1, &p, 0 );
        glCompileShader( _shader );

        params = -1;
        glGetShaderiv( _shader, GL_COMPILE_STATUS, &params );
        LOG(INFO) << "GL_TRUE: " << GL_TRUE << " GL_FALSE: " << GL_FALSE << " PARAMS: " << params;
        if (params != GL_TRUE) {
            PrintShaderCompileInfo( _shader );
            glDeleteShader( _shader );
            _shader = 0;
        }
        shaderfile.close();
    } else {
        LOG(ERROR) << "Shader '" << filename << "' not found.";
        glDeleteShader( _shader );
        _shader = 0;
    }
    return _shader;
}

void Shader::PrintShaderCompileInfo( GLuint shader_index ) {
    int maxlength = 2048;
    int length = 0;
    char log[maxlength];

    glGetShaderInfoLog( shader_index, maxlength, &length, log );
    std::string c( log );
    LOG(ERROR) << c;
}

void Shader::PrintProgramLinkInfo( GLuint program_index ) {
    int maxlength = 2048;
    int length = 0;
    char log[maxlength];

    glGetProgramInfoLog( program_index, maxlength, &length, log );
    std::string c( log );
    LOG(ERROR) << c;
}
