#ifndef GD_LOWL_H
#define GD_LOWL_H

#include "gd_lowl_driver.h"
#include "gd_lowl_error.h"

#include "core/object/class_db.h"

#include <lowl.h>

#include <vector>

class GdLowl : public Object {
GDCLASS(GdLowl, Object);
OBJ_CATEGORY("Lowl Audio");

private:
    static GdLowl *singleton;

private:
    std::vector<Ref<GdLowlDriver>> drivers;

protected:
    static void _bind_methods();

public:
    static GdLowl *get_singleton();

public:
    Array bind_get_drivers();

public:
    std::vector<Ref<GdLowlDriver>> get_drivers();

    GdLowl();

    ~GdLowl();
};



#endif