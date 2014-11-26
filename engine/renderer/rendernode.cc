#include "renderer/rendernode.h"

RenderNode::RenderNode() {

}

RenderNode::~RenderNode() {

}

void RenderNode::Draw() {

}

void RenderNode::Update( double dt ) {
    _time += dt;
    if (_time > 1000.0f) {
        _time = 0.0f;
        _isvisible = !_isvisible;
    }
}

void RenderNode::SetX( float value ) {
    _x0 = value;
}

void RenderNode::SetY( float value ) {
    _y0 = value;
}
