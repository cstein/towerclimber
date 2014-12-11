#include "splashscene.h"

#include "base/faders.h"

SplashScene::SplashScene(TextureManager* texturemanager, std::string texturename, ShaderManager* shadermanager, std::string shadername, double lifetime)
: Scene() {
    _texturemanager = texturemanager;
    _texturename = texturename;
    _shadermanager = shadermanager;
    _shadername = shadername;

    // timers that are constant. Perhaps this should be an object!
    _lifetime = lifetime;
    _steptime = lifetime / FADERSTEPS;

    // this that change over time
    _currenttime = lifetime;
    _currentsteptime = 0.0f;
    _currentstep = 0;


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

void SplashScene::Update( double dt ) {
    if(!_isdead) {
        _currenttime -= dt;
        _currentsteptime += dt;
        if (_currentsteptime >= _steptime) {
            _currentstep += 1;
            _currentsteptime -= _steptime;
            _shadermanager->SetAlpha( FO_LIN[_currentstep-1] );
        }
        if (_currenttime < 0.0f) {
            _isdead = true;
        }
    }
}
