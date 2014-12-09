#include "texturemanager.h"

// 3rd-party includes
#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"

TextureManager::TextureManager() {
    el::Logger* TextureManagerLogger = el::Loggers::getLogger("TextureManager");
    _boundtexture = 0;
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
    if (HasTexture( texturename ))
        return true;

    if (LoadPNG( "resources/graphics/" + texturename + ".png" ))
        return CreateTexture( texturename );

    return false;
}

void TextureManager::BindTexture(std::string texturename) {
    if (HasTexture(texturename)) {
        if (_boundtexture != _textures[texturename]) {
            _boundtexture = _textures[texturename];
        }
        glBindTexture(GL_TEXTURE_2D, _boundtexture);
    }
}

GLuint TextureManager::GetBoundTexture() {
    return _boundtexture;
}

bool TextureManager::LoadPNG( std::string texturename ) {
    CLOG(INFO, "TextureManager") << "Loading '" << texturename << "'.";
    _image.clear();
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
        return 0;
    }
}

bool TextureManager::UnloadTexture( std::string texturename ) {
    if (HasTexture( texturename )) {
        // if the current texture is bound, unbind it before deletion.
        if (_boundtexture == _textures[texturename]) {
            _boundtexture = 0;
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        glDeleteTextures(1, &_textures[texturename]);
        _textures.erase(texturename);
        return true;
    }
    return false;
}
