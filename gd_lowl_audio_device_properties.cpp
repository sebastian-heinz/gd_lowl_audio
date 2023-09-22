#include "gd_lowl_audio_device_properties.h"

void GdLowlAudioDeviceProperties::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_sample_rate"), &GdLowlAudioDeviceProperties::get_sample_rate);
	ClassDB::bind_method(D_METHOD("get_channel"), &GdLowlAudioDeviceProperties::get_channel);
	ClassDB::bind_method(D_METHOD("get_sample_format"), &GdLowlAudioDeviceProperties::get_sample_format);
	ClassDB::bind_method(D_METHOD("is_exclusive_mode"), &GdLowlAudioDeviceProperties::is_exclusive_mode);
	ClassDB::bind_method(D_METHOD("is_supported"), &GdLowlAudioDeviceProperties::is_supported);
	ClassDB::bind_method(D_METHOD("to_info_string"), &GdLowlAudioDeviceProperties::to_info_string);
}

GdLowlAudioDeviceProperties::GdLowlAudioDeviceProperties(Lowl::Audio::AudioDeviceProperties p_audio_device_properties) {
	properties = p_audio_device_properties;
}

GdLowlAudioDeviceProperties::~GdLowlAudioDeviceProperties() {
}

Lowl::Audio::AudioDeviceProperties GdLowlAudioDeviceProperties::get_audio_device_properties() {
	return properties;
}

bool GdLowlAudioDeviceProperties::is_exclusive_mode() {
	return properties.exclusive_mode;
}

GdLowlAudioSource::SampleFormat GdLowlAudioDeviceProperties::get_sample_format() {
	return GdLowlAudioSource::convert_sample_format(properties.sample_format);
}

bool GdLowlAudioDeviceProperties::is_supported() {
	return properties.is_supported;
}

int GdLowlAudioDeviceProperties::get_channel() {
	return Lowl::Audio::get_channel_num(properties.channel);
}

double GdLowlAudioDeviceProperties::get_sample_rate() {
	return properties.sample_rate;
}

String GdLowlAudioDeviceProperties::to_info_string() {
	return String(properties.to_string().c_str());
}
