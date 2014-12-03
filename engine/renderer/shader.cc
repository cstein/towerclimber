#include "shader.h"

#include <sstream>
#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

Shader::Shader() {
    _basepath = "resources/shaders/";
}

Shader::~Shader() {
}

bool Shader::Load() {

    if (_vertexshaderfilename.length() == 0 ) {
        CLOG(ERROR, "Shader") << "Cannot load shader. Vertex shader filename not set.";
        return false;
    }

    if (_fragmentshaderfilename.length() == 0) {
        CLOG(ERROR, "Shader") << "Cannot load shader. Fragment shader filename not set.";
        return false;
    }

    int params;

    _program = glCreateProgram();
    if ( _program != 0 ) {
        _vertexshader = CreateShader(_vertexshaderfilename, GL_VERTEX_SHADER);
        if ( _vertexshader != 0 ) {
            _fragmentshader = CreateShader(_fragmentshaderfilename, GL_FRAGMENT_SHADER);
            if ( _fragmentshader != 0 ) {
                glAttachShader( _program, _vertexshader );
                glAttachShader( _program, _fragmentshader );
                glLinkProgram( _program );
                params = -1;
                glGetProgramiv( _program, GL_LINK_STATUS, &params );
                if ( params != GL_TRUE ) {
                    PrintProgramLinkInfo( _program );
                    CLOG(ERROR, "Shader") << "Could not link shader program: '" << _name <<"'.";
                    Unload();
                    return false;
                }
                SetupShaderLocations();
            } else {
                CLOG(ERROR, "Shader") << "Could not fix fragment shader." << _fragmentshaderfilename;
                Unload();
                return false;
            }
        } else {
            CLOG(ERROR, "Shader") << "Could not fix vertex shader." << _vertexshaderfilename;
            Unload();
            return false;
        }
    }
    CLOG(INFO, "Shader") << "Succesfully compiled and linked shader program: '" << _name << "' at address " << _program << ".";
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

void Shader::SetProjectionMatrix( Eigen::Matrix4f P ) {
    glUniformMatrix4fv( _uniformprojectionmatrix, 1, GL_FALSE, P.data() );
}

void Shader::SetShaderName( std::string name ) {
    _name = name;
}

void Shader::SetVertexShaderFilename( std::string filename ) {
    _vertexshaderfilename = _basepath + filename;
}

void Shader::SetFragmentShaderFilename( std::string filename ) {
    _fragmentshaderfilename = _basepath + filename;
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
        //LOG(INFO) << "GL_TRUE: " << GL_TRUE << " GL_FALSE: " << GL_FALSE << " PARAMS: " << params;
        if (params != GL_TRUE) {
            PrintShaderCompileInfo( _shader );
            glDeleteShader( _shader );
            _shader = 0;
        }
        shaderfile.close();
    } else {
        CLOG(ERROR, "Shader") << "Shader '" << filename << "' not found.";
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
    CLOG(ERROR, "Shader") << c;
}

void Shader::PrintProgramLinkInfo( GLuint program_index ) {
    int maxlength = 2048;
    int length = 0;
    char log[maxlength];

    glGetProgramInfoLog( program_index, maxlength, &length, log );
    std::string c( log );
    CLOG(ERROR, "Shader") << c;
}

void Shader::SetupShaderLocations() {
    SetupShaderAttribLocation( _position, "vertex_position" );
    SetupShaderAttribLocation( _texcoords, "texcoords" );
    SetupShaderUniformLocation( _uniformprojectionmatrix, "projection" );
}

void Shader::SetupShaderAttribLocation( GLuint &attrib, std::string attribname ) {
    attrib = glGetAttribLocation( _program, attribname.c_str() );
    if ( attrib == -1 ) {
        CLOG(WARNING, "Shader") << "Attribute variable '" << attribname << "' not found in '" << _name << "'.";
    } else {
        CLOG(INFO, "Shader") << "Attribute variable '" << attribname << "' in '" << _name << "' has address: " << attrib;
    }
}

void Shader::SetupShaderUniformLocation( GLuint &uniform, std::string uniformname ) {
    uniform = glGetUniformLocation( _program, uniformname.c_str() );
    if ( uniform == -1 ) {
        CLOG(WARNING, "Shader") << "Uniform variable '" << uniformname << "' not found in '" << _name << "'.";
    } else {
        CLOG(INFO, "Shader") << "Uniform variable '" << uniformname << "' in '" << _name << "' has address: " << uniform;
    }
}

bool Shader::Use() {
    if (_program == 0)
        return false;
    glUseProgram( _program );
    return true;
}
