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

    /*
     * if a node is not visible, neither are it's children
     */
    bool IsVisible() { return _isvisible; }
    void Show() { _isvisible = true; }
    void Hide() { _isvisible = false; }
protected:
    std::vector<Vertex2D> _vertices;
    std::vector<Vertex2D> _uvcoordinates;
    GLuint _texture;
    GLuint _vao;
    GLuint _vbo[5];

    GLuint _vattribloc0;
    GLuint _vattribloc1;
    GLuint _vattribloc2;
    GLuint _vattribloc3;
    GLuint _vattribloc4;

    bool _isvisible;
};

#endif
