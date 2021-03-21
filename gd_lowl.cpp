#include "gd_lowl.h"

GdLowl *GdLowl::singleton = nullptr;

GdLowl *GdLowl::get_singleton() {
    return singleton;
}

void GdLowl::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_drivers"), &GdLowl::bind_get_drivers);
}

GdLowl::GdLowl() {
    drivers = std::vector<Ref<GdLowlDriver>>();
    singleton = this;
    Lowl::Error error;
    Lowl::Lib::initialize(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::GdLowl:initialize: error: %d", error.get_error_code()));
        return;
    }
    std::vector<Lowl::Driver *> lowl_drivers = Lowl::Lib::get_drivers(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::GdLowl:get_drivers: error: %d", error.get_error_code()));
        return;
    }
    for (Lowl::Driver *lowl_driver : lowl_drivers) {
        GdLowlDriver *gd_driver = memnew(GdLowlDriver(lowl_driver));
        Ref<GdLowlDriver> gd_driver_ref = Ref<GdLowlDriver>(gd_driver);
        drivers.push_back(gd_driver_ref);
    }
}

GdLowl::~GdLowl() {
    Lowl::Error error;
    Lowl::Lib::terminate(error);
    if (error.has_error()) {
        print_line(vformat("GdLowl::~GdLowl: error: %d", error.get_error_code()));
        return;
    }
}

Array GdLowl::bind_get_drivers() {
    Array gd_drivers = Array();
    for (Ref<GdLowlDriver> driver : drivers) {
        gd_drivers.push_back(driver);
    }
    return gd_drivers;
}

std::vector<Ref<GdLowlDriver>> GdLowl::get_drivers() {
    return std::vector<Ref<GdLowlDriver>>(drivers);
}
