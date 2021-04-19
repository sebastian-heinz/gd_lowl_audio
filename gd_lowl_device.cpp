#include "gd_lowl_device.h"

void GdLowlDevice::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDevice::get_name);
    ClassDB::bind_method(D_METHOD("start", "audio_source"), &GdLowlDevice::start);
    ClassDB::bind_method(D_METHOD("stop"), &GdLowlDevice::stop);
    ClassDB::bind_method(D_METHOD("is_supported", "audio_source"), &GdLowlDevice::is_supported_source);
    ClassDB::bind_method(D_METHOD("is_supported", "channel", "sample_rate", "sample_format"), &GdLowlDevice::is_supported);
    ClassDB::bind_method(D_METHOD("get_default_sample_rate"), &GdLowlDevice::get_default_sample_rate);
}

GdLowlDevice::GdLowlDevice(std::shared_ptr<Lowl::Device> p_device) {
    device = p_device;
}

GdLowlDevice::~GdLowlDevice() {

}

GdLowlError::Code GdLowlDevice::stop() {
    Lowl::Error err;
    device->stop(err);
    return GdLowlError::convert(err.get_error());
}

String GdLowlDevice::get_name() const {
    return String(device->get_name().c_str());
}

GdLowlError::Code GdLowlDevice::start(const Ref<GdLowlAudioSource> &p_audio_source) {
    Lowl::Error err;
    device->start(p_audio_source->get_audio_source(), err);
    return GdLowlError::convert(err.get_error());
}

bool GdLowlDevice::is_supported_source(const Ref<GdLowlAudioSource> &p_audio_source) {
    Lowl::Error err;
    bool supported = device->is_supported(p_audio_source->get_audio_source(), err);
    return supported;
}

double GdLowlDevice::get_default_sample_rate() {
    return device->get_default_sample_rate();
}

bool GdLowlDevice::is_supported(int p_channel, double p_sample_rate, GdLowlAudioSource::SampleFormat p_sample_format) {
    Lowl::Error err;
    bool supported = device->is_supported((Lowl::Channel)p_channel, p_sample_rate, (Lowl::SampleFormat)p_sample_format, err);
    return supported;
}
