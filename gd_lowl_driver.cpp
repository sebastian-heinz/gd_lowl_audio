#include "gd_lowl_driver.h"

void GdLowlDriver::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_devices"), &GdLowlDriver::get_devices);
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDriver::get_name);
    ClassDB::bind_method(D_METHOD("initialize"), &GdLowlDriver::initialize);
    ClassDB::bind_method(D_METHOD("get_default_device"), &GdLowlDriver::get_default_device);
}

GdLowlDriver::GdLowlDriver(std::shared_ptr<Lowl::AudioDriver> p_driver) {
    driver = p_driver;
    default_device = Ref<GdLowlDevice>();
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
    std::vector<std::shared_ptr<Lowl::AudioDevice>> lowl_devices = driver->get_devices();
    print_line(vformat("GdLowlDriver::initialize: lowl_devices.size(): %d", (int) lowl_devices.size()));
    for (std::shared_ptr<Lowl::AudioDevice> lowl_device : lowl_devices) {
        GdLowlDevice *gd_device = memnew(GdLowlDevice(lowl_device));
        Ref<GdLowlDevice> gd_device_ref = Ref<GdLowlDevice>(gd_device);
        devices.push_back(gd_device_ref);
        if (lowl_device == driver->get_default_device()) {
            default_device = gd_device_ref;
        }
    }
    return GdLowlError::Code::NoError;
}

String GdLowlDriver::get_name() const {
    return String(driver->get_name().c_str());
}

Array GdLowlDriver::get_devices() const {
    Array gd_devices = Array();
    for (Ref<GdLowlDevice> device : devices) {
        gd_devices.push_back(device);
    }
    return gd_devices;
}

Ref<GdLowlDevice> GdLowlDriver::get_default_device() const {
    return default_device;
}
