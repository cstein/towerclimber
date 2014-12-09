#include "texturemanager.h"

// 3rd-party includes
#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"

TextureManager::TextureManager() {
    el::Logger* TextureManagerLogger = el::Loggers::getLogger("TextureManager");
}

TextureManager::~TextureManager() {
    el::Loggers::unregisterLogger("TextureManager");
}

void TextureManager::Start() {

}

void TextureManager::Stop() {

}

bool TextureManager::HasTexture( std::string texturename ) {
    return GetTextureID( texturename ) != 0;
}

bool TextureManager::LoadTexture( std::string texturename ) {
    bool success = false;
    if (LoadPNG( "resources/graphics/" + texturename + ".png" )) {
        success = CreateTexture( texturename );
        _image.clear(); // will sometimes crash - perhaps the uploading to GFX is not complete.
        //CLOG(INFO, "TextureManager") << "le id: " << glGetError();
    }
    return success;
}

void TextureManager::BindTexture(std::string texturename) {

}

GLuint TextureManager::GetBoundTexture() {
    return 0;
}

bool TextureManager::LoadPNG( std::string texturename ) {
    CLOG(INFO, "TextureManager") << "Loading '" << texturename << "'.";
    unsigned int error = lodepng::decode(_image, _imagewidth, _imageheight, texturename.c_str());
    if (error != 0) {
        CLOG(ERROR, "TextureManager") << lodepng_error_text(error);
        return false;
    }
    return true;
}

bool TextureManager::CreateTexture( std::string texturename ) {
    _textures[texturename] = 0;
    glGenTextures(1, &_textures[texturename]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imagewidth, _imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_image[0]);

    // unbind the texture for now
    glBindTexture(GL_TEXTURE_2D, 0);
    return (_textures[texturename] != 0);
}


GLuint TextureManager::GetTextureID( std::string texturename ) {
    std::map<std::string, GLuint>::iterator it = _textures.find( texturename );
    if (it != _textures.end()) {
        return it->second;
    } else {
        CLOG(ERROR, "TextureManager") << "Texture '" << texturename << "' not found.";
        return 0;
    }
}
