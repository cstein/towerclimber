#include "texture.h"

#include "easyloggingpp/src/easylogging++.h"
#include "lodepng/lodepng.h"

Texture::Texture() {
    _id = 0;
    _isbound = false;
}

void Texture::Bind() {
    if( !HasID() ) {
        // if the texture has not been created yet, or somehow was unloaded,
        // then reload it here so we can bind it later on.
        Create();
    }

    if( !IsBound() ) {
        glBindTexture(GL_TEXTURE_2D, _id);
        //_isbound = true;
    }
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    _isbound = false;
}

// Assumes that the texture is no longer bound, i.e. it is the
// job of the TextureManager to ensure that the texture is not bound
// when it is deleted.
void Texture::Destroy() {
    glDeleteTextures(1, &_id);
}

bool Texture::Load() {
    if (LoadPNG()) {
        return Create();
    }
    return false;
}

bool Texture::LoadPNG() {
    CLOG(INFO, "Texture") << "Loading '" << _filename << "'.";
    _data.clear();
    unsigned int error = lodepng::decode(_data, _width, _height, _filename.c_str());
    if (error != 0) {
        CLOG(ERROR, "Texture") << lodepng_error_text(error);
        return false;
    }
    return true;
}

bool Texture::Create() {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // transfer the texture to the graphics card
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_data[0]);

    // unbind the texture for now
    Unbind();

    return true;
}

