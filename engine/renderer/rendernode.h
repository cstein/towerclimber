#ifndef __RENDERNODE_H_
#define __RENDERNODE_H_

#include <vector>
#include <GL/glew.h>

struct Vertex2D {
    float x;
    float y;
};

/*
 * Basic rendernode class.
 *
 * A single rendernode can have 1 VAO and up to 5 VBOs
 */
class RenderNode {
public:
    RenderNode();
    ~RenderNode();
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
};

#endif
