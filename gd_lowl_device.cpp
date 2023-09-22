#include "gd_lowl_device.h"

#include <vector>

void GdLowlDevice::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &GdLowlDevice::get_name);
	ClassDB::bind_method(D_METHOD("start", "audio_properties", "audio_source"), &GdLowlDevice::start);
	ClassDB::bind_method(D_METHOD("stop"), &GdLowlDevice::stop);
	ClassDB::bind_method(D_METHOD("get_properties"), &GdLowlDevice::get_properties);
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

Array GdLowlDevice::get_properties() const {
	std::vector<Lowl::Audio::AudioDeviceProperties> audio_properties = device->get_properties();
	Array gd_audio_properties = Array();

	for (int i = 0; i < audio_properties.size(); i++) {
		Ref<GdLowlAudioDeviceProperties> gd_audio_property = Ref<GdLowlAudioDeviceProperties>(memnew(GdLowlAudioDeviceProperties(audio_properties[i])));
		gd_audio_properties.push_back(gd_audio_property);
	}
	return gd_audio_properties;
}

GdLowlError::Code GdLowlDevice::start(const Ref<GdLowlAudioDeviceProperties> &p_audio_properties, const Ref<GdLowlAudioSource> &p_audio_source) {
	Lowl::Error err;
	device->start(
			p_audio_properties->get_audio_device_properties(),
			p_audio_source->get_audio_source(),
			err);
	if (err.has_error()) {
		print_error(vformat("GdLowl::GdLowlDevice:start: error: %d", err.get_error_code()));
	}
	GdLowlError::Code code = GdLowlError::convert(err.get_error());
	print_line(vformat("GdLowl::GdLowlDevice: start: %d", code));
	return code;
}
