#ifndef GD_LOWL_NODE_H
#define GD_LOWL_NODE_H

#include "core/object/class_db.h"
#include "scene/main/node.h"

class GdLowlNode : public Node {
GDCLASS(GdLowlNode, Node);

protected:
    static void _bind_methods();

public:
    GdLowlNode();

    ~GdLowlNode();

};


#endif //GD_LOWL_NODE_H
