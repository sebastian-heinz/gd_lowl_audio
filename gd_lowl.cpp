#include "gd_lowl.h"

#include "lowl.h"

GdLowl *GdLowl::singleton = nullptr;

GdLowl *GdLowl::get_singleton() {
    return singleton;
}

void GdLowl::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_drivers"), &GdLowl::get_drivers);
    ClassDB::bind_method(D_METHOD("init"), &GdLowl::init);
    ClassDB::bind_method(D_METHOD("finish"), &GdLowl::finish);
}

GdLowl::GdLowl() {
    drivers = std::vector<Ref<GdLowlDriver>>();
    singleton = this;
}

GdLowl::~GdLowl() {

}

Array GdLowl::get_drivers() {
    Array gd_drivers = Array();
    for (Ref<GdLowlDriver> driver : drivers) {
        gd_drivers.push_back(driver);
    }
    return gd_drivers;
}

GdLowlError::Code GdLowl::finish() {
    Lowl::Error error;
    Lowl::Lib::terminate(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::~GdLowl: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    return GdLowlError::NoError;
}

GdLowlError::Code GdLowl::init() {
    Lowl::Error error;
    Lowl::Lib::initialize(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::GdLowl:initialize: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    std::vector<Lowl::Driver *> lowl_drivers = Lowl::Lib::get_drivers(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::GdLowl:get_drivers: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    for (Lowl::Driver *lowl_driver : lowl_drivers) {
        GdLowlDriver *gd_driver = memnew(GdLowlDriver(lowl_driver));
        Ref<GdLowlDriver> gd_driver_ref = Ref<GdLowlDriver>(gd_driver);
        drivers.push_back(gd_driver_ref);
    }
    return GdLowlError::NoError;
}
