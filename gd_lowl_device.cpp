#include "gd_lowl_device.h"

void GdLowlDevice::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDevice::get_name);
    ClassDB::bind_method(D_METHOD("start", "audio_source"), &GdLowlDevice::start);
    ClassDB::bind_method(D_METHOD("stop"), &GdLowlDevice::stop);
    ClassDB::bind_method(D_METHOD("is_source_supported", "audio_source"), &GdLowlDevice::is_supported_source);
    ClassDB::bind_method(D_METHOD("is_format_supported", "channel", "sample_rate", "sample_format"),
                         &GdLowlDevice::is_supported);
    ClassDB::bind_method(D_METHOD("get_default_sample_rate"), &GdLowlDevice::get_default_sample_rate);
    ClassDB::bind_method(D_METHOD("set_exclusive_mode", "exclusive_mode"), &GdLowlDevice::set_exclusive_mode);
    ClassDB::bind_method(D_METHOD("is_exclusive_mode"), &GdLowlDevice::is_exclusive_mode);
}

GdLowlDevice::GdLowlDevice(std::shared_ptr<Lowl::Audio::AudioDevice> p_device) {
    device = p_device;
}

GdLowlDevice::~GdLowlDevice() {

}

GdLowlError::Code GdLowlDevice::stop() {
    Lowl::Error err;
    device->stop(err);
    if (err.has_error()) {
        print_error(vformat("GdLowl::GdLowlDevice:stop: error: %d", err.get_error_code()));
    }
    GdLowlError::Code code = GdLowlError::convert(err.get_error());
    print_line(vformat("GdLowl::GdLowlDevice: stop: %d", code));
    return code;
}

String GdLowlDevice::get_name() const {
    return String(device->get_name().c_str());
}

GdLowlError::Code GdLowlDevice::start(const Ref<GdLowlAudioSource> &p_audio_source) {
    Lowl::Error err;
    device->start(p_audio_source->get_audio_source(), err);
    if (err.has_error()) {
        print_error(vformat("GdLowl::GdLowlDevice:start: error: %d", err.get_error_code()));
    }
    GdLowlError::Code code = GdLowlError::convert(err.get_error());
    print_line(vformat("GdLowl::GdLowlDevice: start: %d", code));
    return code;
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
    bool supported = device->is_supported((Lowl::Audio::AudioChannel) p_channel, p_sample_rate,
                                          (Lowl::Audio::SampleFormat) p_sample_format, err);
    return supported;
}

void GdLowlDevice::set_exclusive_mode(bool p_exclusive_mode) {
    Lowl::Error err;
    device->set_exclusive_mode(p_exclusive_mode, err);
}

bool GdLowlDevice::is_exclusive_mode() const {
    return device->is_exclusive_mode();
}
