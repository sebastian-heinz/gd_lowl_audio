#ifndef GD_LOWL_AUDIO_DEVICE_PROPERTIES_H
#define GD_LOWL_AUDIO_DEVICE_PROPERTIES_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

#include "gd_lowl_audio_source.h"

#include "audio/lowl_audio_device_properties.h"

class GdLowlAudioDeviceProperties : public RefCounted {
	GDCLASS(GdLowlAudioDeviceProperties, RefCounted);

private:
	GdLowlAudioDeviceProperties(){
		//ClassDB::register_class<GdLowlAudioDeviceProperties>();
	};

private:
	Lowl::Audio::AudioDeviceProperties properties;

protected:
	static void _bind_methods();

public:
	GdLowlAudioDeviceProperties(Lowl::Audio::AudioDeviceProperties p_audio_device_properties);

	Lowl::Audio::AudioDeviceProperties get_audio_device_properties();

	double get_sample_rate();

	int get_channel();

	GdLowlAudioSource::SampleFormat get_sample_format();

	bool is_exclusive_mode();

	bool is_supported();

	String to_info_string();

	~GdLowlAudioDeviceProperties();
};

#endif //GD_LOWL_AUDIO_DEVICE_PROPERTIES_H
