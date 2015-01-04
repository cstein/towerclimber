#ifndef __NODE_H_
#define __NODE_H_

#include <vector>

/*
 * Represents a basic task (node) that can be carried out.
 *   * Renderer
 *
 */

class Node {
public:
    virtual ~Node() {}
    virtual void Update( double dt ) = 0;
    virtual void Draw() = 0;
};

#endif
