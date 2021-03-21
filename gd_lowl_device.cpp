#include "gd_lowl_device.h"

GdLowlDevice::GdLowlDevice(Lowl::Device *p_device) {
    device = p_device;
}

GdLowlDevice::~GdLowlDevice() {

}

GdLowlError::Code GdLowlDevice::stop() {
    return GdLowlError::Code::NoError;
}

GdLowlError::Code GdLowlDevice::start() {
    return GdLowlError::Code::NoError;
}

GdLowlError::Code GdLowlDevice::play() {
    return GdLowlError::Code::NoError;
}

std::string GdLowlDevice::get_name() const {
    return device->get_name();
}

String GdLowlDevice::bind_get_name() const {
    return String(get_name().c_str());
}

void GdLowlDevice::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDevice::bind_get_name);
}
