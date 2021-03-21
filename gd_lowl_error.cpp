#include "gd_lowl_error.h"


void GdLowlError::_bind_methods() {
    BIND_ENUM_CONSTANT(Error);
    BIND_ENUM_CONSTANT(NoError);
}

GdLowlError::Code GdLowlError::convert(Lowl::ErrorCode error) {
    switch (error) {
        case Lowl::ErrorCode::NoError:
            return GdLowlError::Code::NoError;
        case Lowl::ErrorCode::Error:
            return GdLowlError::Code::Error;
    }
    return GdLowlError::Code::NoError;
}