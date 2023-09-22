#ifndef GD_LOWL_DEVICE_H
#define GD_LOWL_DEVICE_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

#include "gd_lowl_audio_source.h"
#include "gd_lowl_audio_device_properties.h"
#include "gd_lowl_error.h"

#include "audio/lowl_audio_device.h"

class GdLowlDevice : public RefCounted {
	GDCLASS(GdLowlDevice, RefCounted);

private:
	GdLowlDevice() {
		// ClassDB::register_class<GdLowlDevice>();
		device = nullptr;
	};

private:
	std::shared_ptr<Lowl::Audio::AudioDevice> device;

protected:
	static void _bind_methods();

public:
	String get_name() const;

	GdLowlError::Code start(const Ref<GdLowlAudioDeviceProperties> &p_audio_device_properties, const Ref<GdLowlAudioSource> &p_audio_source);

	GdLowlError::Code stop();

	Array get_properties() const;

	GdLowlDevice(std::shared_ptr<Lowl::Audio::AudioDevice> p_device);

	~GdLowlDevice();
};

#endif //GD_LOWL_DEVICE_H
