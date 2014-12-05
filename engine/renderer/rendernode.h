#ifndef __RENDERNODE_H_
#define __RENDERNODE_H_

#include <vector>
#include <string>
#include <GL/glew.h>

#include "base/node.h"
#include "renderer/shadermanager.h"


struct Vertex2D {
    float x;
    float y;
};

/*
 * Basic rendernode class.
 *
 * A single rendernode can have 1 VAO and up to 5 VBOs
 */
class RenderNode : public Node {
public:
    RenderNode();
    ~RenderNode();

    /* Attaches a shader to the RenderNode.
     */
    virtual void AttachShader( ShaderManager* sm, std::string shadername );

    virtual void Draw();
    virtual void Update( double dt );

    /*
     * if a node is not visible, neither are it's children
     */
    bool IsVisible() { return _isvisible; }
    void Show() { _isvisible = true; }
    void Hide() { _isvisible = false; }

    virtual void SetX( float x );
    virtual void SetY( float y );
    virtual float GetX() { return _x0; }
    virtual float GetY() { return _y0; }
    virtual bool CreateVAO();
    virtual void DestroyVAO();

    virtual bool HasShaderAttached() { return _shadername != ""; }

protected:
    std::vector<Vertex2D> _vertices;
    std::vector<Vertex2D> _uvcoordinates;
    GLuint _texture;
    GLuint _vao;
    GLuint _vbo[5];
    GLuint _vattribloc[5];
    bool _vattribactive[5];

    bool _isvisible;

    // internal time counter. In milliseconds.
    double _time;

    float _x0;
    float _y0;

    std::string _shadername;
    ShaderManager* _shadermanager;
};

#endif
