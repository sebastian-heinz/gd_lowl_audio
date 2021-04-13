#ifndef GD_LOWL_DEVICE_H
#define GD_LOWL_DEVICE_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"
#include "gd_lowl_audio_source.h"

#include "lowl_device.h"

class GdLowlDevice : public Reference {
GDCLASS(GdLowlDevice, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    GdLowlDevice() {
        // ClassDB::register_class<GdLowlDevice>();
        device = nullptr;
    };

private:
    Lowl::Device *device;

protected:
    static void _bind_methods();

public:
    bool is_supported(int p_channel, double p_sample_rate, GdLowlAudioSource::SampleFormat p_sample_format);

    double get_default_sample_rate();

    bool is_supported(const Ref<GdLowlAudioSource> &p_audio_source);

    String get_name() const;

    GdLowlError::Code start(const Ref<GdLowlAudioSource> &p_audio_source);

    GdLowlError::Code stop();

    GdLowlDevice(Lowl::Device *p_device);

    ~GdLowlDevice();
};

#endif //GD_LOWL_DEVICE_H
