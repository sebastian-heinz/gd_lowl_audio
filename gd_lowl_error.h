#ifndef GD_LOWL_ERROR_H
#define GD_LOWL_ERROR_H

#include <lowl_error.h>

#include "core/object/class_db.h"

class GdLowlError : public Object {
GDCLASS(GdLowlError, Object);
OBJ_CATEGORY("Lowl Audio");

public:
    enum Code {
        NoError = (int) Lowl::ErrorCode::NoError,
        Error = (int) Lowl::ErrorCode::Error,
    };

private:
    GdLowlError() {};

protected:
    static void _bind_methods();

public:
    static GdLowlError::Code convert(Lowl::ErrorCode error);
};

VARIANT_ENUM_CAST(GdLowlError::Code)

#endif //GD_LOWL_ERROR_H
