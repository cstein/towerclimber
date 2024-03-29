#include "shadermanager.h"

#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

ShaderManager::ShaderManager( SettingsManager* settings ) {
    el::Logger* FontManagerLogger = el::Loggers::getLogger("ShaderManager");
    el::Logger* FontLogger = el::Loggers::getLogger("Shader");
    _currentshaderid = 0;
    _currentshader = nullptr;
    _uniform_alpha = 1.0f;
    _settings = settings;
}

ShaderManager::~ShaderManager() {
    el::Loggers::unregisterLogger("Shader");
    el::Loggers::unregisterLogger("ShaderManager");
}

void ShaderManager::Start() {
    if (_settings == nullptr) {
        CLOG(ERROR, "ShaderManager") << "Invalid SettingManager provided.";
        return;
    }

    if (!_settings->HasSettingsPath("shaders")) {
        CLOG(ERROR, "ShaderManager") << "Settings for shaders not provided.";
        return;
    }

    SettingsPath* settingspath = _settings->GetSettingsPath("shaders");
    _confpath = settingspath->GetPath();
    _confname = settingspath->GetName();
    std::string conffilename = _confpath + "/" + _confname;

    std::ifstream shaderconf;
    std::stringstream buffer;
    std::string shadername;
    jsonxx::Array shaders;
    jsonxx::Object shader;
    std::string vertexfilename;
    std::string fragmentfilename;

    shaderconf.open( conffilename );
    if ( shaderconf.is_open() ) {
        buffer << shaderconf.rdbuf();
        if ( _configuration.parse( buffer ) ) {
            CLOG(INFO, "ShaderManager") << "Configuration loaded.";
            shaders = _configuration.get<jsonxx::Array>("shaders");
            CLOG(INFO, "ShaderManager") <<  "Found " << shaders.size() << " shader(s).";
            for( int i=0; i<shaders.size(); i++) {
                shadername = shaders.get<jsonxx::String>(i);
                if ( _configuration.has<jsonxx::Object>( shadername ) ){
                    CLOG(INFO, "ShaderManager") << "Loading '" << shadername << "'.";
                    shader = _configuration.get<jsonxx::Object>( shadername );
                    vertexfilename = shader.get<jsonxx::String>("vert");
                    fragmentfilename = shader.get<jsonxx::String>("frag");

                    _shaders[shadername] = Shader();
                    _shaders[shadername].SetShaderName( shadername );
                    _shaders[shadername].SetVertexShaderFilename( vertexfilename );
                    _shaders[shadername].SetFragmentShaderFilename( fragmentfilename );
                    if (!_shaders[shadername].Load() ) {
                        CLOG(ERROR, "ShaderManager") << "Error loading shader.";
                        _shaders.erase( shadername );
                    }
                } else {
                    CLOG(ERROR, "ShaderMananger") << "Could not find shader: '" << shadername << "' in .json file.";
                }
            }
        } else {
            CLOG(ERROR, "ShaderManager") << "Could not parse .json file.";
        }
        shaderconf.close();
    } else {
        CLOG(ERROR, "ShaderManager") << "Configuration file 'resources/shaders/shaders.json' not found.";
    }
}

void ShaderManager::Stop() {

}

Shader* ShaderManager::GetShader( std::string shadername ) {
    std::map<std::string, Shader>::iterator it = _shaders.find( shadername );
    if (it != _shaders.end()) {
        return &it->second;
    } else {
        return nullptr;
    }
}

bool ShaderManager::HasShader( std::string shadername ) {
    return GetShader(shadername) != nullptr;
}


bool ShaderManager::BindShader( std::string shadername ) {
    if (!HasShader( shadername ))
        return false;
    Shader* s = GetShader( shadername );

    // if the current shader is not the one we ask for, bind it.
    if (s->GetID() != _currentshaderid) {
        _currentshaderid = s->GetID();
        _currentshader = s;
        if (s->Use()) {
            s->SetProjectionMatrix( _uniform_projection_matrix );
            s->SetAlpha( _uniform_alpha );
        }
    }

    return true;
}

void ShaderManager::SetProjectionMatrix( Eigen::Matrix4f P ) {
    _uniform_projection_matrix = P;
}

void ShaderManager::SetAlpha( float value ) {
    _uniform_alpha = value;
}
