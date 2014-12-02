#include "shadermanager.h"

#include <fstream>

#include "easyloggingpp/src/easylogging++.h"

ShaderManager::ShaderManager() {
    el::Logger* FontManagerLogger = el::Loggers::getLogger("ShaderManager");
    el::Logger* FontLogger = el::Loggers::getLogger("Shader");
}

ShaderManager::~ShaderManager() {
    el::Loggers::unregisterLogger("Shader");
    el::Loggers::unregisterLogger("ShaderManager");
}

void ShaderManager::Start() {
    std::ifstream shaderconf;
    std::stringstream buffer;
    std::string shadername;
    jsonxx::Array shaders;
    jsonxx::Object shader;
    std::string vertexfilename;
    std::string fragmentfilename;

    shaderconf.open("resources/shaders/shaders.json");
    if ( shaderconf.is_open() ) {
        buffer << shaderconf.rdbuf();
        if ( _configuration.parse( buffer ) ) {
            CLOG(INFO, "ShaderManager") << "Configuration loaded.";
            shaders = _configuration.get<jsonxx::Array>("shaders");
            CLOG(INFO, "ShaderManager") <<  "Found " << shaders.size() << " shader.";
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
//Font* FontManager::Get(std::string fontname) {
//    std::map<std::string, Font>::iterator it = _fonts.find( fontname );
//    if (it != _fonts.end()) {
//        return &it->second;
//    } else {
//        CLOG(ERROR, "FontManager") << "Font '" << fontname << "' not found.";
//        return nullptr;
//    }
//}

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
