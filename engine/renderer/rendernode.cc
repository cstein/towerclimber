#include "renderer/rendernode.h"

#include <iostream>

RenderNode::RenderNode() {
    _x0 = 0.0f;
    _y0 = 0.0f;
    _isvisible = true;
    _vao = 0;

    // vertex attribute locations are set when they are used and made active
    // at the same time. Here, we only set if they are active.
    for( int i=0; i<5; i++ ) {
        _vbo[i] = 0;
        _vattribactive[i] = false;
    }


}

RenderNode::~RenderNode() {
    int n_vbo = 0;
    for( int i=0; i<5; i++ ) {
        if (_vbo[i] > 0) {
            n_vbo += 1;
        }
        if (_vattribactive[i] == true) {
            glDisableVertexAttribArray(_vattribloc[i]);
        }
    }
    if (n_vbo > 0) {
        glDeleteBuffers(n_vbo, _vbo);
    }
    if (_vao != 0 ) {
        glDeleteVertexArrays(1, &_vao);
    }

}

void RenderNode::Draw() {

}

void RenderNode::Update( double dt ) {
}

void RenderNode::SetX( float value ) {
    _x0 = value;
}

void RenderNode::SetY( float value ) {
    _y0 = value;
}
