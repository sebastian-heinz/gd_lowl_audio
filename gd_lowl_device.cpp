#include "gd_lowl_device.h"

void GdLowlDevice::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDevice::get_name);
    ClassDB::bind_method(D_METHOD("start_mixer", "mixer"), &GdLowlDevice::start_mixer);
    ClassDB::bind_method(D_METHOD("stop"), &GdLowlDevice::stop);
}

GdLowlDevice::GdLowlDevice(Lowl::Device *p_device) {
    device = p_device;
}

GdLowlDevice::~GdLowlDevice() {

}

GdLowlError::Code GdLowlDevice::stop() {
    Lowl::Error err;
    device->stop(err);
    return GdLowlError::convert(err.get_error());
}

GdLowlError::Code GdLowlDevice::start_mixer(const Ref<GdLowlAudioMixer> &p_mixer) {
    Lowl::Error err;
    device->start(p_mixer->get_audio_mixer(), err);
    return GdLowlError::convert(err.get_error());
}

String GdLowlDevice::get_name() const {
    return String(device->get_name().c_str());
}