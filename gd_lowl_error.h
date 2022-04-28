#ifndef GD_LOWL_ERROR_H
#define GD_LOWL_ERROR_H

#include "core/object/class_db.h"

#include "lowl_error.h"

class GdLowlError : public Object {
GDCLASS(GdLowlError, Object);

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
