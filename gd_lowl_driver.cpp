#include "gd_lowl_driver.h"

void GdLowlDriver::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_devices"), &GdLowlDriver::bind_get_devices);
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDriver::bind_get_name);
    ClassDB::bind_method(D_METHOD("initialize"), &GdLowlDriver::initialize);
}

GdLowlDriver::GdLowlDriver(Lowl::Driver *p_driver) {
    driver = p_driver;
}

GdLowlDriver::~GdLowlDriver() {

}

GdLowlError::Code GdLowlDriver::initialize() {
    Lowl::Error error;
    driver->initialize(error);
    if (error.has_error()) {
        return GdLowlError::convert(error.get_error());
    }
    devices = std::vector<Ref<GdLowlDevice>>();
    std::vector<Lowl::Device *> lowl_devices = driver->get_devices();
    print_line(vformat("GdLowlDriver::initialize: lowl_devices.size(): %d", (int) lowl_devices.size()));
    for (Lowl::Device *lowl_device : lowl_devices) {
        GdLowlDevice *gd_device = memnew(GdLowlDevice(lowl_device));
        Ref<GdLowlDevice> gd_device_ref = Ref<GdLowlDevice>(gd_device);
        devices.push_back(gd_device_ref);
    }
    return GdLowlError::Code::NoError;
}

std::vector<Ref<GdLowlDevice>> GdLowlDriver::get_devices() const {
    return std::vector<Ref<GdLowlDevice>>(devices);
}

std::string GdLowlDriver::get_name() const {
    return driver->get_name();
}

String GdLowlDriver::bind_get_name() const {
    return String(get_name().c_str());
}

Array GdLowlDriver::bind_get_devices() const {
    Array gd_devices = Array();
    for (Ref<GdLowlDevice> device : devices) {
        gd_devices.push_back(device);
    }
    return gd_devices;
}