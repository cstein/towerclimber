#include "splashscene.h"

SplashScene::SplashScene(TextureManager* texturemanager, std::string texturename, ShaderManager* shadermanager, std::string shadername, float lifetime) {
    _texturemanager = texturemanager;
    _texturename = texturename;
    _shadermanager = shadermanager;
    _shadername = shadername;
    _lifetime = lifetime;

    texturemanager->LoadTexture( texturename );

    /*
     * The SplashScene contains a single basic object and a SplashNode attached to that.
     */
    splashobject = new Object();
    splashobject->SetParentScene( this );
    splashobject->SetDrawable( true );

    /*
     * Only a single SplashNode is added.
     */
    splashnode = new SplashNode();
    splashnode->AttachShader(shadermanager, shadername );
    splashnode->AttachTextureManager( texturemanager );
    splashnode->Create( texturename );
    splashnode->Show();

    splashobject->AddNode( splashnode );

    this->AddObject( splashobject );
}

SplashScene::~SplashScene() {
    _texturemanager->UnloadTexture( _texturename );
    _texturemanager = nullptr;

    _shadermanager = nullptr;
}
